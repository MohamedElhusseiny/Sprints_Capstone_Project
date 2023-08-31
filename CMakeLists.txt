cmake_minimum_required(VERSION 3.22)

project( Capstone_Proj
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_CROSS_COMPILER_PREFIX aarch64-rpi4-linux-gnu-)

set(CMAKE_C_COMPILER /home/elhusseiny/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc-9.4.0)
set(CMAKE_CXX_COMPILER /home/elhusseiny/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++)

set(CMAKE_FIND_ROOT_PATH /home/elhusseiny/x-tools/aarch64-rpi4-linux-gnu/)

# call logger lib "to create this static lib"
add_subdirectory(boost_logger_lib)

# build mesagge queue files
add_subdirectory(message_queue_lib)

# build math app
add_subdirectory(math_app)

# build daemon app
add_subdirectory(logger_daemon_app)