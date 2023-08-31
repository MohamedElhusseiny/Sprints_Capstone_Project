# set source files
set(DAEMON_SRC
    container_class.cpp
    threads_handler.cpp
    config_file_handler.cpp
    lg_daemon_app.cpp)

# add libs dir to the daemon file
set(DAEMON_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../message_queue_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../boost_logger_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

# add executable
add_executable(daemon_app ${DAEMON_SRC})

# add compiler options for daemon
target_compile_options(daemon_app PUBLIC -std=c++17)

target_link_libraries(daemon_app PRIVATE -lrt -lpthread)


# add include files
target_include_directories(daemon_app PRIVATE ${DAEMON_INC})
message("My variable contains: ${DAEMON_INC}")


# link daemon with boost_logger
target_link_libraries(daemon_app PRIVATE BoostLogger_lib)

# link daemon with boost_logger
target_link_libraries(daemon_app PRIVATE MQ_lib)

install(TARGETS daemon_app)