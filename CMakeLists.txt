cmake_minimum_required(VERSION 3.22)

project( Capstone_Proj
        VERSION 2.0
        LANGUAGES CXX)

######################################################
# compile for rpi4 target with cross ng build compiler

# set TEST_ON_HOST macro with "true" if you want to build project with native compiler
set(TEST_ON_HOST "true")
set(TARGET_RPI_VERSION "RPI4")

if(NOT ${TEST_ON_HOST} STREQUAL "true" AND ${TARGET_RPI_VERSION} STREQUAL "RPI4")
    message("
    Build Project for RPI4 target")
    set(CMAKE_CXX_COMPILER "/home/elhusseiny/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++")
elseif(NOT ${TEST_ON_HOST} STREQUAL "true" AND ${TARGET_RPI_VERSION} STREQUAL "RPI3")
    message("Build Project for RPI3 target")
    set(CMAKE_SYSTEM_PROCESSOR armv7l)
    set(CMAKE_CXX_COMPILER "/home/elhusseiny/x-tools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-g++")
else()
    message("Build Project for native test purpose")
endif()

######################################################
# build mesagge queue shared & static libs
add_subdirectory(message_queue_lib)

######################################################
# build boost logger shared & static libs
add_subdirectory(boost_logger_lib)

######################################################
# build math application
add_subdirectory(math_app)

######################################################
# build daemon application
add_subdirectory(logger_daemon_app)

######################################################
# build host app consider that it will be in host 
# compile with native compiler
add_subdirectory(host_app)

######################################################