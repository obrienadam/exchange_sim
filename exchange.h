#pragma once

#include <string_view>
#include <unordered_map>

#include "order_queue.h"

using OrderQueueMap = std::unordered_map<std::string_view, OrderQueue>;

class Exchange{
    public:

    const OrderQueueMap& view_order_queue(std::string_view ticker) const;

    private:

    OrderQueueMap order_queues_{};
};
