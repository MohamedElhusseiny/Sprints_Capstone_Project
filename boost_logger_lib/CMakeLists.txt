###################################
# create static lib

cmake_minimum_required(VERSION 3.2)
project(boost_logger_static_lib)


set(Boost_INCLUDE_DIR /home/elhusseiny/Downloads/boost/boost_rpi/boost_1_80_0)
set(Boost_LIBRARY_DIR /home/elhusseiny/Downloads/boost/boost_rpi/boost_1_80_0/stage/lib)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.74 COMPONENTS log log_setup system thread REQUIRED)
# find_package(Boost REQUIRED COMPONENTS log)



include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_library(BoostLogger_lib logger.cpp logger.hpp)

target_link_libraries(BoostLogger_lib ${Boost_LIBRARIES} pthread)
