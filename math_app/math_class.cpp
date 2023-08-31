/**
 * @file math_class.cpp
 * @author mohamed ahmed elhusseiny
 * @brief 
 * @version 0.1
 * @date 2023-08-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include "math_class.hpp"

double Calculator::add(double a, double b) 
{
    return a + b;
}

double Calculator::subtract(double a, double b) 
{
    return a - b;
}

double Calculator::multiply(double a, double b) 
{
    return a * b;
}

double Calculator::divide(double a, double b) 
{
    if (b != 0) 
    {
        return a / b;
    }
    else 
    {
        std::cerr << "Error: Division by zero" << std::endl;
        return 0.0;
    }
}

void Calculator::help(void) 
{
    std::cout << "Mathematical Operation Applications" << std::endl;
    std::cout << "Available choices:" << std::endl;
    std::cout << " + : Addition" << std::endl;
    std::cout << " - : Subtraction" << std::endl;
    std::cout << " x : Multiplication" << std::endl;
    std::cout << " / : Division" << std::endl;
    std::cout << "example : [./program_name num1 x num2]" << std::endl;
}