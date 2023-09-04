######################################################
# create static and shared library

cmake_minimum_required(VERSION 3.22)

# set source file
set(    MQ_SRC
        mq_posix_wraper.cpp
)

# creat static lib
add_library(MQ_lib_static STATIC ${MQ_SRC})

# creat shared lib
add_library(MQ_lib_shared SHARED ${MQ_SRC})

# link with real time libs 
target_link_libraries(MQ_lib_static PUBLIC -lrt)

# link with real time libs 
target_link_libraries(MQ_lib_shared PUBLIC -lrt)