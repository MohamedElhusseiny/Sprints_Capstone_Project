/**
 * @file server_tcp.hpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef     SERVER_CONNECT_H
#define     SERVER_CONNECT_H

class Server
{
private:
    int server_socket_id;

public:
    void create_socket();                                   /* can be constructor */
    int get_socket_id();        /* return server_socket_id value */
    std::string get_ip_address(const std::string &interface_name);
    void send_log_to_client(int client_id , const std::string &message);
};

#endif