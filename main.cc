#include <iostream>
#include <queue>
#include <string>
#include <optional>
#include <algorithm>

struct Order{
    enum Type {
        MARKET = 0,
        LIMIT = 1
    };

    enum Action {
        BUY = 0, SELL = 1
    };

    int agent_id{0};
    std::string symbol;
    int num_shares{0};
    Action action{BUY};
    Type type{MARKET};

    std::optional<double> limit_price{std::nullopt};
};

class OrderQueue{
    public:
 
    protected:

    void add_buy_order(const Order& order) {
        constexpr auto cmp = [](const Order& lhs, const Order& rhs)->bool {
            if(lhs.type != rhs.type) {
                return lhs.type > rhs.type;
            }

            if(lhs.type == Order::MARKET) {
                return lhs.num_shares < rhs.num_shares;
            }

            return lhs.limit_price.value() < rhs.limit_price.value();
        };

        std::push_heap(buy_orders_.begin(), buy_orders_.end(), cmp);
    }

    void add_sell_order(const Order& order) {
                constexpr auto cmp = [](const Order& lhs, const Order& rhs)->bool {
            if(lhs.type != rhs.type) {
                return lhs.type > rhs.type;
            }

            if(lhs.type == Order::MARKET) {
                return lhs.num_shares < rhs.num_shares;
            }

            return lhs.limit_price.value() > rhs.limit_price.value();
        };

        std::push_heap(sell_orders_.begin(), sell_orders_.end(), cmp);
    }

    std::vector<Order> buy_orders_;
    std::vector<Order> sell_orders_;
};

int main(int argc, const char **argv) {
    using namespace std;



    return 0;
}
