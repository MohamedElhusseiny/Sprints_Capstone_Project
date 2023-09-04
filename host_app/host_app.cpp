/**
 * @file host_app.cpp
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
#include "host_app.hpp"

int main() 
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        std::cerr << "Connection failed" << std::endl;
        close(client_socket);
        return 1;
    }

    std::cout << "Connected to the server at " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    char buffer[1024]; /* max log file size */
    while (true)
    {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) 
        {
            std::cerr << "Connection closed or error occurred" << std::endl;
            break;
        }
        buffer[bytes_received] = '\0';      // Null-terminate the received data
        std::cout << buffer << std::endl;
    }

    close(client_socket);
    return 0;
}
