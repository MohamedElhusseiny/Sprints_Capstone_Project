/**
 * @file threads_handler.cpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "container_class.hpp"
#include "threads_handler.hpp"
#include "logger.hpp"
#include "severity_helper.hpp"

std::mutex log_Mutex;

void mq_threads_handler(MessageQueueReceiver *mq_ptr) 
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); /*  sleep for duration */
        
        std::string message{};
        size_t delimiter_pos{};
        std::string extract_message{};
        int severity_num{-1};
        
        mq_ptr->receive_sync(message);
        std::lock_guard<std::mutex> lock(log_Mutex);

        delimiter_pos = message.find(":");

        /* Extract the message and severity level */
        extract_message = message.substr(0, delimiter_pos);
        severity_num = std::stoi(message.substr(delimiter_pos + 1));

        /* handle which sevarity level send to */
        switch(severity_num)
        {
            case TRACE_NUM:
                LOG_TRACE << extract_message;
                break;
            case DEBUG_NUM:
                LOG_DEBUG << extract_message;
                break;
            case INFO_NUM:
                LOG_INFO << extract_message;
                break;
            case WARNING_NUM:
                LOG_WARNING << extract_message;
                break;
            case ERROR_NUM:
                LOG_ERROR << extract_message;
                break;
            case FATAL_NUM:
                LOG_FATAL << extract_message;
                break;
            default : 
                LOG_TRACE << "there is a message discard due to wrong severity";
                break;
        }
    }
}
