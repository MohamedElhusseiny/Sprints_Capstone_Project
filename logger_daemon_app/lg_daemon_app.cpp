/**
 * @file lg_daemon.cpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <thread>
#include "mq_posix_wraper.hpp"
#include "logger.hpp"
#include "container_class.hpp"
#include "config_file_handler.hpp"
#include "threads_handler.hpp"

#if 1



int main()
{
    init_logging();

    const std::string CONFIG_FILE_NAME = "/etc/daemon_logger_etc/MQ_config.txt";
    const std::string APP_NAME  = "DAEMON Server ";
    std::map<std::string, std::string> config_data = read_config_file(CONFIG_FILE_NAME);

    // Create message queues
    int number_of_mqs = std::stoi(config_data["number_of_message_queues"]);
    std::vector<std::thread> threads;
    /* container to all mqs and fill it */
    /* it can be access with each process name */
    MessageQueueContainer mq_container;

    for (int i = 1; i <= number_of_mqs; i++) 
    {
        std::string queue_name_key = "message_queue_" + std::to_string(i) + "_name";
        std::string process_name_key = "message_queue_" + std::to_string(i) + "_application";

        std::string queue_name = "/" + config_data[queue_name_key];
        std::string process_name = config_data[process_name_key];
        
        /* create each queue */
        mq_container.add_message_queue(queue_name , process_name , true);
        LOG_TRACE << APP_NAME << "link process: " << process_name << " with: " << queue_name;
        /* thread creation */
        threads.emplace_back(mq_threads_handler, mq_container.get_message_queue(process_name));
    }

    /* Wait for all threads to finish */ 
    for (std::thread& thread : threads) 
    {
        thread.join();
    }

    LOG_TRACE << APP_NAME << "Exit";
    return 0;
}


#endif