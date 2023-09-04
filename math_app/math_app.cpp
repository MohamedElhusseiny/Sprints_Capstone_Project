/**
 * @file math_app.cpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include "mq_posix_wraper.hpp"
#include "severity_helper.hpp"
#include "math_class.hpp"

int main(int argc, char* argv[]) 
{
    MessageQueueSender mq_sender;
    int error_status =  mq_sender.connect("/queue1");
    if(error_status == -1)
    {
        std::cerr << "faild to connect with message queue\n";
        return 1;
    }
    mq_sender.send("start math app" , TRACE_NUM);

    Calculator calculator;
    if (argc == 2 && std::string(argv[1]) == "--help") 
    {
        calculator.help();
        mq_sender.send("programe exit after print help message to user" , TRACE_NUM);
        return 0;
    }

    if (argc != 4) 
    {
        mq_sender.send("programe exit Invalid number of arguments. use --help" , ERROR_NUM);
        std::cerr << "exit with  Invalid number of arguments. Use '--help' for usage information." << std::endl;
        return 1;
    }

    double operand1 = std::stod(argv[1]);
    char choice = argv[2][0];
    double operand2 = std::stod(argv[3]);
    double result = 0.0;

    switch (choice) 
    {
        case '+':
            result = calculator.add(operand1, operand2);
            mq_sender.send("add two numbers and exit" , TRACE_NUM);
            break;
        case '-':
            result = calculator.subtract(operand1, operand2);
            mq_sender.send("sub two numbers and exit" , TRACE_NUM);
            break;
        case 'x':
            result = calculator.multiply(operand1, operand2);
            mq_sender.send("multibly two numbers and exit" , TRACE_NUM);
            break;
        case '/':
            result = calculator.divide(operand1, operand2);
            mq_sender.send("divide two numbers and exit" , TRACE_NUM);
            break;
        default:
            mq_sender.send("exit with Invalid choice. Use '--help' for available choices." , ERROR_NUM);
            std::cerr << "Invalid choice. Use '--help' for available choices." << std::endl;
            return 1;
    }

    std::cout << "Result: " << result << std::endl;
    mq_sender.send("exit after printing the result" , ERROR_NUM);
    return 0;
}