/**
 * @file message_queue_lib.cpp
 * @author mohamed ahmed elhusseiny
 * @brief  message queue library using posix api
 * @version 0.1
 * @date 2023-08-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cerrno>
#include <cstring>
#include "mq_posix_wraper.hpp"

/***********************************************************************************************
/***********************************************************************************************
 * MessageQueueReceiver class
*/


/**
 * @brief Construct a new Message Queue Receiver:: Message Queue Receiver object
 * 
 * @param queue_name name of the queue that will create
 * @param process_name name of the process that will comunicate over this mq
 */
MessageQueueReceiver::MessageQueueReceiver(const std::string &queue_name , const std::string &process_name , bool block_state)
{
    /**
     * 1- create new message queue
     * 2- get mq descriptor
    */
    std::string error_msg{};
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MQ_NUM;
    attr.mq_msgsize = MAX_MQ_SIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;


    int o_flag_value = O_CREAT | O_RDONLY;
    if(block_state == false)        /* enable non blocking */
    {
        o_flag_value = O_CREAT | O_RDONLY | O_NONBLOCK;
    }

    mq_descriptor =  mq_open(queue_name.c_str(), o_flag_value, 0666, &attr);
    if(mq_descriptor == -1)
    {
        error_msg = strerror(errno);
        std::cout << errno;
        std::cerr << "mq_open failed: " << error_msg << std::endl;
    }
    /* set private id with the name of application */
    this->private_id = process_name;
    this->block_state = block_state;        /* to check in receive_async */
    this->queue_name = queue_name;
}

/**
 * @brief create mq object will create new mq under /dev/mqueue/
 * 
 * @param queue_name name of queue
 * @param process_name name of process
 * @param block_state  state block or not block with receive
 * @return error_t  if success return 1 and -1 if error
 */
error_t MessageQueueReceiver::create(const std::string &queue_name , const std::string &process_name , bool block_state)
{
    /**
     * 1- create new message queue
     * 2- get mq descriptor
    */
    error_t error_state{1};
    std::string error_msg{};
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MQ_NUM;
    attr.mq_msgsize = MAX_MQ_SIZE;

    int o_flag_value = O_CREAT | O_RDONLY;
    if(block_state == false)        /* enable non blocking */
    {
        o_flag_value = O_CREAT | O_RDONLY | O_NONBLOCK;
    }

    mq_descriptor =  mq_open(queue_name.c_str(), o_flag_value, 0666, &attr);
    if(mq_descriptor == -1)
    {
        error_msg = strerror(errno);
        std::cerr << "mq_open failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }

    /* set private id with the name of application */
    this->private_id = process_name;
    this->block_state = block_state;        /* to check in receive_async */
    this->queue_name = queue_name;

    return error_state;
}

MessageQueueReceiver::~MessageQueueReceiver()
{
    mq_close(this->mq_descriptor);
    mq_unlink(this->queue_name.c_str());
}

/**
 * @brief receive message over mq name synchronizationly.
 * 
 * @param message_rec 
 * @return error_t  if success return 1 and -1 if error
 */
error_t MessageQueueReceiver::receive_sync(std::string &message_rec)
{
    error_t error_state{1};
    std::string error_msg{};
    
    struct mq_attr attr;                    /* get attribute info */ 
    int ret_value = mq_getattr(mq_descriptor, &attr);
    if(ret_value == -1)
    {
        error_msg = strerror(errno);
        std::cerr << "mq_getattr failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }

    char cString_message[attr.mq_msgsize];  /* create c string temp */
    /* recieve in buffer */
    int received_size{}; 
    received_size = mq_receive(mq_descriptor, cString_message, attr.mq_msgsize, NULL);
    if (received_size == -1 )
    {
        error_msg = strerror(errno);
        std::cerr << "mq_receive failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }
    
    /* sepreate sevarity from message */
    cString_message[received_size] = '\0';          /* do you need it !? is sender didn't send it or what ?*/
    message_rec = cString_message;
    /* [prog name] message:severity_level */
    message_rec = "[ " + this->private_id + " ] " + message_rec;

    return error_state;
}

/**
 * @brief receive message over mq name Asynchronizationly.
 * 
 * @param message_rec 
 * @return error_t  if success return 1 and -1 if error
 */
error_t MessageQueueReceiver::receive_async(std::string &message_rec)
{
    error_t error_state{1};
    std::string error_msg{};
    if(this->block_state == true)           /* send async is not supported */
    {
        error_state = -1;
        return error_state;
    }
    
    struct mq_attr attr;                    /* get attribute info */ 
    int ret_value = mq_getattr(mq_descriptor, &attr);
    if(ret_value == -1)
    {
        error_msg = strerror(errno);
        std::cerr << "mq_getattr failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }

    char cString_message[attr.mq_msgsize];  /* create c string temp */
    /* recieve in buffer */
    int received_size{}; 
    received_size = mq_receive(mq_descriptor, cString_message, attr.mq_msgsize, NULL);
    if (received_size == -1 && errno != EAGAIN) /* check in error but ignore if that about the empty buffer */
    {
        error_msg = strerror(errno);
        std::cerr << "mq_receive failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }

    cString_message[received_size] = '\0';          /* do you need it !? is sender didn't send it or what ?*/
    message_rec = cString_message;
    message_rec = "[ " + this->private_id + " ] " + message_rec;

    return error_state;
}

/***********************************************************************************************
/***********************************************************************************************
 * MessageQueueSender class

/**
 * @brief connect function use to get mq_descriptor that will use when sending to this mq
 * 
 * @param queue_name name of queue
 * @return error_t  if success return 1 and -1 if error
 */
error_t MessageQueueSender::connect(const std::string &queue_name)
{
    /**
     * 1- open the message queue connection
     * 2- get mq descriptor
    */
    error_t error_state{1};
    std::string error_msg{};

    /* O_WRONLY as the sender need to write to this mq */
    mq_descriptor =  mq_open(queue_name.c_str(), O_WRONLY);
    if(mq_descriptor == -1)
    {
        error_msg = strerror(errno);
        std::cerr << "mq_open failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }
    return error_state;
}


/**
 * @brief send cross mq
 * 
 * @param message to send
 * @param severity_level the level of severity message
 * 
 * @return error_t  if success return 1 and -1 if error
 */
error_t MessageQueueSender::send(const std::string &message , const int &severity_level)
{
    error_t error_state{1};
    std::string error_msg{};

    int msq_send_res{};
    std::string new_message{};
    new_message = message + ":" + std::to_string(severity_level);   /* message:severity_level */
    msq_send_res = mq_send(mq_descriptor, new_message.c_str(), new_message.length() + 1, 1);
    if(msq_send_res == -1) 
    {
        error_msg = strerror(errno);
        std::cerr << "mq_open failed: " << error_msg << std::endl;
        error_state = -1;
        return error_state;
    }
    return error_state;
}

MessageQueueSender::~MessageQueueSender()
{
    mq_close(this->mq_descriptor);
}