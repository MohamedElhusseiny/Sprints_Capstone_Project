/**
 * @file threads_handller.hpp
 * @author mohamed  ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef THREADS_HADLLER_H
#define THREADS_HADLLER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include "container_class.hpp"

void mq_threads_handler(MessageQueueReceiver *mq_ptr);


#endif