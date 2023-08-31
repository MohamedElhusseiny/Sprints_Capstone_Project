/**
 * @file container_class.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef     CONTAINER_H
#define     CONTAINER_H

#include <map>
#include <memory>
#include "mq_posix_wraper.hpp"


class MessageQueueContainer 
{
private:
    /* to store each message queue with id number */
    std::multimap<std::string, std::unique_ptr<MessageQueueReceiver>> message_queues_container;

public:
    void add_message_queue(const std::string& queue_name, const std::string& application_name , bool block_state);
    MessageQueueReceiver* get_message_queue(const std::string& application_name);
    ~MessageQueueContainer();
};

#endif