#include "order_queue.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <unordered_map>

bool OrderQueue::BuyComparator::operator()(size_t lhs_id, size_t rhs_id) const {
  const auto &lhs = map_->at(lhs_id);
  const auto &rhs = map_->at(rhs_id);

  if (lhs.type != rhs.type) {
    return lhs.type < rhs.type;
  }

  if (lhs.type == Order::MARKET) {
    return lhs.num_shares > rhs.num_shares;
  }

  return lhs.limit_price.value() > rhs.limit_price.value();
}

bool OrderQueue::SellComparator::operator()(size_t lhs_id,
                                            size_t rhs_id) const {
  const auto &lhs = map_->at(lhs_id);
  const auto &rhs = map_->at(rhs_id);

  if (lhs.type != rhs.type) {
    return lhs.type < rhs.type;
  }

  if (lhs.type == Order::MARKET) {
    return lhs.num_shares < rhs.num_shares;
  }

  return lhs.limit_price.value() < rhs.limit_price.value();
}

OrderQueue::OrderQueue() {
  buy_orders_ = decltype(buy_orders_)(BuyComparator(&orders_));
  sell_orders_ = decltype(sell_orders_)(SellComparator(&orders_));
}

size_t OrderQueue::place_order(const Order &order, OrderCallback callback) {
  orders_.emplace(next_order_id_, order);
  callbacks_.emplace(next_order_id_, std::move(callback));

  switch (order.action) {
  case Order::BUY:

    queue_buy_order(next_order_id_);
    break;
  case Order::SELL:
    queue_sell_order(next_order_id_);
    break;
  }

  return next_order_id_++;
}

void OrderQueue::queue_buy_order(size_t buy_order_id) {
  auto &buy_order = orders_.at(buy_order_id);

  while (buy_order.num_shares > 0 && !sell_orders_.empty()) {
    auto it = sell_orders_.begin();
    size_t sell_order_id = *it;

    auto &sell_order = orders_.at(sell_order_id);

    if (buy_order.limit_price.value_or(
            std::numeric_limits<double>::infinity()) <
        sell_order.limit_price.value()) {
      // Cannot continue trading.
      sell_orders_.insert(sell_order_id);
      break;
    }

    sell_orders_.erase(it);

    int num_shares_to_trade =
        std::min(buy_order.num_shares, sell_order.num_shares);

    buy_order.num_shares -= num_shares_to_trade;
    sell_order.num_shares -= num_shares_to_trade;

    OrderFulfilled order_fulfilled{.buying_agent_id = buy_order.agent_id,
                                   .selling_agent_id = sell_order.agent_id,
                                   .num_shares = num_shares_to_trade,
                                   .filled_price =
                                       sell_order.limit_price.value()};

    callbacks_.at(buy_order_id)(order_fulfilled);
    callbacks_.at(sell_order_id)(order_fulfilled);

    if (sell_order.num_shares == 0) {
      orders_.erase(sell_order_id);
      callbacks_.erase(sell_order_id);
    } else {
      sell_orders_.emplace_hint(sell_orders_.begin(), sell_order_id);
    }
  }

  if (buy_order.num_shares > 0) {
    buy_orders_.insert(buy_order_id);
  } else {
    orders_.erase(buy_order_id);
    callbacks_.erase(buy_order_id);
  }
}

void OrderQueue::queue_sell_order(size_t sell_order_id) {
  auto &sell_order = orders_.at(sell_order_id);

  while (sell_order.num_shares > 0 && !buy_orders_.empty()) {
    auto it = buy_orders_.begin();
    size_t buy_order_id = *it;

    auto &buy_order = orders_.at(buy_order_id);

    if (buy_order.limit_price.value() < sell_order.limit_price.value_or(0.)) {
      // Cannot continue trading.
      break;
    }

    buy_orders_.erase(it);

    int num_shares_to_trade =
        std::min(sell_order.num_shares, buy_order.num_shares);

    sell_order.num_shares -= num_shares_to_trade;
    buy_order.num_shares -= num_shares_to_trade;

    OrderFulfilled order_fulfilled{.buying_agent_id = buy_order.agent_id,
                                   .selling_agent_id = sell_order.agent_id,
                                   .num_shares = num_shares_to_trade,
                                   .filled_price =
                                       buy_order.limit_price.value()};

    callbacks_.at(buy_order_id)(order_fulfilled);
    callbacks_.at(sell_order_id)(order_fulfilled);

    if (buy_order.num_shares == 0) {
      orders_.erase(buy_order_id);
      callbacks_.erase(buy_order_id);
    } else {
      buy_orders_.emplace_hint(buy_orders_.begin(), buy_order_id);
    }
  }

  if (sell_order.num_shares > 0) {
    sell_orders_.insert(sell_order_id);
  } else {
    orders_.erase(sell_order_id);
    callbacks_.erase(sell_order_id);
  }
}

void OrderQueue::remove_order(size_t id) {
  orders_.erase(id);
  callbacks_.erase(id);
}

std::vector<Order> OrderQueue::get_buy_orders() const {
  std::vector<Order> orders;

  for (size_t id : buy_orders_) {
    orders.push_back(orders_.at(id));
  }

  return orders;
}

std::vector<Order> OrderQueue::get_sell_orders() const {
  std::vector<Order> orders;

  for (size_t id : sell_orders_) {
    orders.push_back(orders_.at(id));
  }

  return orders;
}

std::ostream &operator<<(std::ostream &os, const OrderFulfilled &order) {
  os << order.buying_agent_id << " -> " << order.selling_agent_id
     << ": Shares: " << order.num_shares << " at $" << order.filled_price;
  return os;
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
  constexpr auto action_to_str = [](Order::Action action) -> std::string {
    switch (action) {
    case Order::BUY:
      return "BUY";
    case Order::SELL:
      return "SELL";
    }
  };

  constexpr auto type_to_str = [](Order::Type type) -> std::string {
    switch (type) {
    case Order::MARKET:
      return "MARKET";
    case Order::LIMIT:
      return "LIMIT";
    }
  };

  os << action_to_str(order.action) << ' ' << type_to_str(order.type) << ' '
     << order.limit_price.value_or(0.) << " " << order.num_shares;
  return os;
}
