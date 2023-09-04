cmake_minimum_required(VERSION 3.22)

project( Capstone_Proj
        VERSION 2.0
        LANGUAGES CXX)

# compile for host / not include in the project compilation stage

set(HOST_APP_SRC
    host_app.cpp)

set( HOST_APP_INC
    ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(host_application ${HOST_APP_SRC})

# add compiler options for host application
target_compile_options(host_application PUBLIC -std=c++17)

# add include files
target_include_directories(host_application PRIVATE ${HOST_APP_INC})

install(TARGETS host_application)