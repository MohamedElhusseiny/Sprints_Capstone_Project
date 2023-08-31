/**
 * @file message_queue_lib.hpp
 * @author mohamed ahmed elhusseiny
 * @brief  message queue library using posix api
 * @version 0.1
 * @date 2023-08-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MQ_LIB_H
#define MQ_LIB_H
#include <mqueue.h>

#define     MAX_MQ_SIZE     150
#define     MAX_MQ_NUM     10

class MessageQueueReceiver
{
private:
    mqd_t mq_descriptor;
    std::string private_id; /* name for process that connect on mq  */
    std::string queue_name;
    bool block_state;
public:
    MessageQueueReceiver() = delete;   // delete key word to ensure that this constructor not use
    explicit MessageQueueReceiver(const std::string &queue_name , const std::string &process_name , bool block_state);
    error_t create(const std::string &queue_name , const std::string &process_name , bool block_state);
    error_t receive_sync(std::string &message_rec);
    error_t receive_async(std::string &message_rec );
    ~MessageQueueReceiver();                        /* Deinit "close all sessions" */
};


class MessageQueueSender
{
private:
    mqd_t mq_descriptor;

public:
    error_t connect(const std::string &queue_name);
    error_t send(const std::string &message , const int &severity_level);
    ~MessageQueueSender();                        /* Deinit "close all sessions" */
};

#endif