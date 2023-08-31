/**
 * @file config_file_handler.cpp
 * @author moahemd ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <map>
#include <iostream>
#include <fstream>
#include "config_file_handler.hpp"
#include "logger.hpp"

std::map<std::string, std::string> read_config_file(const std::string& filename) 
{
    std::map<std::string, std::string> config_data;
    std::string key{};
    std::string value{};
    std::ifstream config_file(filename);
    if (!config_file.is_open()) 
    {
        LOG_ERROR << "failed to open config file: " << filename;
        exit(1);
    }

    std::string line;
    while (std::getline(config_file, line)) 
    {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) 
        {
            key = line.substr(0, delimiterPos);
            value = line.substr(delimiterPos + 1);
            config_data[key] = value;
        }
        else
        {
            LOG_WARNING << "error in config file formate";
        }
    }

    config_file.close();
    return config_data;
}