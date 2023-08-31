/**
 * @file container_class.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <map>
#include <memory>
#include "mq_posix_wraper.hpp"
#include "container_class.hpp"

void MessageQueueContainer::add_message_queue(const std::string& queue_name, const std::string& application_name , bool block_state) 
{
    auto mq = std::make_unique<MessageQueueReceiver>(queue_name, application_name , block_state);
    message_queues_container.emplace(application_name, std::move(mq));
}


MessageQueueReceiver* MessageQueueContainer::get_message_queue(const std::string& application_name) 
{
    auto range = message_queues_container.equal_range(application_name);
    for (auto iter = range.first; iter != range.second; iter++) 
    {
        if (iter->second) {
            return iter->second.get();
        }
    }
    return nullptr;
}

MessageQueueContainer::~MessageQueueContainer() 
{
    message_queues_container.clear();
}