
###################################
# create static lib for mq
cmake_minimum_required(VERSION 3.2)
project(mq_posix_static_lib)

add_library(MQ_lib mq_posix_wraper.cpp mq_posix_wraper.hpp)

target_link_libraries(MQ_lib PUBLIC -lrt)


###################################