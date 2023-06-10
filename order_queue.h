#pragma once

#include <algorithm>
#include <cstddef>
#include <mutex>
#include <optional>
#include <ostream>
#include <set>
#include <unordered_map>
#include <vector>

struct Order {
  enum Type { MARKET = 0, LIMIT = 1 };

  enum Action { BUY = 0, SELL = 1 };

  int agent_id{0};
  int num_shares{0};
  Action action{BUY};
  Type type{MARKET};

  std::optional<double> limit_price{std::nullopt};
};

struct OrderFulfilled {
  int buying_agent_id;
  int selling_agent_id;
  int num_shares;
  double filled_price;
};

class OrderQueue {
public:
  using OrderCallback = std::function<void(const OrderFulfilled &)>;

  OrderQueue();
  OrderQueue(const OrderQueue &) = delete;

  OrderQueue &operator=(const OrderQueue &) = delete;

  size_t place_order(
      const Order &order,
      OrderCallback callback = [](const OrderFulfilled &) {});

  std::vector<Order> get_buy_orders() const;

  std::vector<Order> get_sell_orders() const;

protected:
  using IdOrderMap = std::unordered_map<size_t, Order>;

  class BuyComparator {
  public:
    BuyComparator(IdOrderMap *map = nullptr) : map_(map) {}

    bool operator()(size_t lhs_id, size_t rhs_id) const;

  private:
    IdOrderMap *map_;
  };

  class SellComparator {
  public:
    SellComparator(IdOrderMap *map = nullptr) : map_(map) {}

    bool operator()(size_t lhs_id, size_t rhs_id) const;

  private:
    IdOrderMap *map_;
  };

  void try_fulfill_buy_order(const Order &order);

  void queue_buy_order(size_t id);

  void queue_sell_order(size_t id);

  void remove_order(size_t id);

  std::mutex mu_;

  std::set<size_t, BuyComparator> buy_orders_;
  std::set<size_t, SellComparator> sell_orders_;

  std::unordered_map<size_t, OrderCallback> callbacks_;
  std::unordered_map<size_t, Order> orders_;

  size_t next_order_id_{0};
};

std::ostream &operator<<(std::ostream &os, const OrderFulfilled &order);
std::ostream &operator<<(std::ostream &os, const Order &order);
