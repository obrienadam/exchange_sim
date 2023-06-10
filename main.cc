#include <iostream>
#include <random>

#include "order_queue.h"

int main(int argc, const char **argv) {
  using namespace std;
  std::mt19937_64 gen;

  std::uniform_int_distribution<int> agent_dist(0, 20);
  std::uniform_int_distribution<size_t> random_int;
  std::normal_distribution<double> price_distribution(40., 3.);
  std::uniform_int_distribution<int> share_dist(30, 100);

  OrderQueue orders;

  Order::Action actions[] = {Order::BUY, Order::SELL};
  Order::Type types[] = {Order::LIMIT, Order::MARKET};

  for (int i = 0; i < 150; ++i) {
    Order order{
        .agent_id = agent_dist(gen),
        .num_shares = share_dist(gen),
        .action = actions[random_int(gen) % 2],
        .type = Order::LIMIT,
    };

    if (order.type == Order::LIMIT) {
      order.limit_price = price_distribution(gen);
    }

    orders.place_order(order, [order](const OrderFulfilled &order_fulfilled) {
      double limit_price = order.limit_price.value();

      std::cout << order_fulfilled << '\n';

      switch (order.action) {
      case Order::BUY:
        std::cout << "Price improvement (BUY): "
                  << limit_price - order_fulfilled.filled_price << '\n';
        break;
      case Order::SELL:
        std::cout << "Price improvement (SELL): "
                  << order_fulfilled.filled_price - limit_price << '\n';
      }
    });
  }

  return 0;
}
