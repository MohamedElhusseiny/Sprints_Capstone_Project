/**
 * @file config_file_handler.hpp
 * @author moahmed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CONFIG_FILE_HANDLE_H
#define CONFIG_FILE_HANDLE_H
/**
 * @brief read cofiguartion data from MQ_config.txt
 * 
 * @param filename MQ_config.txt
 * @return std::map<std::string, std::string> 
 */
std::map<std::string, std::string> read_config_file(const std::string& filename);

#endif