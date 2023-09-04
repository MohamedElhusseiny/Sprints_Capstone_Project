/**
 * @file server.cpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include "server_class.hpp"
#include "logger.hpp"
#include "lg_daemon.hpp"

std::string Server::get_ip_address(const std::string &interface_name)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, interface_name.c_str(), IFNAMSIZ - 1);
    ioctl(sockfd, SIOCGIFADDR, &ifr);
    close(sockfd);
    return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);
}

void Server::send_log_to_client(int client_id , const std::string &message)
{
    // first check if there is connection or not
    // send message
    if(client_id <= 0)
    {
        LOG_INFO << APP_NAME << "socket is not connect yet so data can't send to any host";
        return ;
    }
    std::string message_with_delimiter = message + "\n";
    send(client_id, message_with_delimiter.c_str(), message_with_delimiter.size(), 0);
    LOG_TRACE << APP_NAME << "sending message through socket";
}

int Server::get_socket_id()
{
    return this->server_socket_id;
}


void Server::create_socket()
{
    std::string interface_name = "wlan0";
    std::string ipAddress = get_ip_address(interface_name);
    // const char* server_ip = ipAddress.c_str();
    const char* server_ip = "127.0.0.1";
    int server_port = 11478;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        LOG_ERROR << APP_NAME << "Socket creation failed";
        return ;
    }

    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("Setsockopt failed");
        return ;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        LOG_ERROR << APP_NAME << "Socket Bind failed";
        close(server_socket);
        return ;
    }

    if (listen(server_socket, 5) == -1) { // Allow up to 5 pending connections
        LOG_ERROR << APP_NAME << "Socket Listen failed";
        close(server_socket);
        return ;
    }

    std::cout << "Listening for connections on " << server_ip << ":" << server_port << std::endl;
    LOG_TRACE << APP_NAME << "Listening for connections on " << std::string(server_ip) << ":" << std::to_string(server_port);
    
    this->server_socket_id = server_socket;
}