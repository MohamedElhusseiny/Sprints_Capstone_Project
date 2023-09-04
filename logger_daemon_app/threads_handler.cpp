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
#include <queue>
#include <condition_variable>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include "lg_daemon.hpp"
#include "container_class.hpp"
#include "threads_handler.hpp"
#include "logger.hpp"
#include "severity_helper.hpp"
#include "server_class.hpp"


std::mutex log_Mutex;
std::queue<std::string> threads_message_queue;  // for signaling between threads
std::condition_variable cv;                     // for signaling between threads


void mq_threads_handler(MessageQueueReceiver *mq_ptr) 
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); /*  sleep for duration */
        
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
        
        /* Send the log message directly to the client */
        threads_message_queue.push(message);        // Add the message to the queue
        cv.notify_one();                            // Notify the consumer thread that a message is available

    }
}


/**
 * @brief server thread handler : listen to every new connection
 * 
 * @param server_obj single instatnce of Server class 
 */
void server_thread_handler(Server &server_obj) 
{
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    
    int client_socket_id = accept(server_obj.get_socket_id() , (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket_id == -1) 
    {
        LOG_ERROR << APP_NAME << "Socket Accept failed";
        return;
    }
    LOG_TRACE << APP_NAME << "Accepted connection from " << std::string(inet_ntoa(client_addr.sin_addr)) << ":" << std::to_string(ntohs(client_addr.sin_port));
    const std::string wellcome_message = "Connection open successfully welcome";
    send(client_socket_id, wellcome_message.c_str(), wellcome_message.size(), 0);
    
    std::cout << "Accepted connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
    // std::cout << "Accepted connection from " << server_obj.get_ip_address("wlp2s0") << ":" << ntohs(client_addr.sin_port) << std::endl;
    LOG_TRACE << APP_NAME << "client socket id :" << client_socket_id;

    while(true)
    {
        std::unique_lock<std::mutex> lock(log_Mutex);
        /* Wait until a message is available in the queue */ 
        cv.wait(lock, [] { return !threads_message_queue.empty(); });
        std::string server_message;
        server_message = threads_message_queue.front(); // Get the message from the queue
        threads_message_queue.pop(); // Remove the message from the queue
        server_obj.send_log_to_client(client_socket_id , server_message);
    }
    close(client_socket_id);
}