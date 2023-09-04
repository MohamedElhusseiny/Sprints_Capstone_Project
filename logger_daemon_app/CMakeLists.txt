###############################################################
# set boost variables

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

# Check if you test on host or not
if(NOT ${TEST_ON_HOST} STREQUAL "true")
    if(${TARGET_RPI_VERSION} STREQUAL "RPI4")
        message("Build boost lib for RPI4 target")
        set(BOOST_ROOT "/home/elhusseiny/boost_rpi4")
        set(Boost_INCLUDE_DIR "/home/elhusseiny/boost_rpi4/include/")
    elseif(${TARGET_RPI_VERSION} STREQUAL "RPI3")
        message("Build boost lib for RPI3 target")
        set(CMAKE_SYSTEM_PROCESSOR armv7l)
        set(Boost_ARCHITECTURE "arm")
        set(BOOST_ROOT "/home/elhusseiny/boost_rpi3")
        set(Boost_INCLUDE_DIR "/home/elhusseiny/boost_rpi3/include")
        set(Boost_LIBRARY_DIRS "/home/elhusseiny/boost_rpi3/lib")
    else()
        message("Build boost lib for native test purpose")
    endif()
else()
    message("Test on host, no need to change boost settings")
endif()


find_package(Boost REQUIRED COMPONENTS log log_setup system thread)

include_directories(${Boost_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIRS})

message(status "*** Boost include dir: ${Boost_INCLUDE_DIR} ***")
message(status "*** Boost library dir: ${Boost_LIBRARY_DIRS} ***")
message(status "*** Boost libs: ${Boost_LIBRARIES} ***")

###############################################################
# create excutable daemon app:

# set source files var
set(    DAEMON_SRC
        container_class.cpp
        server_class.cpp
        threads_handler.cpp
        config_file_handler.cpp
        lg_daemon_app.cpp
    )


# setinc dirs to the daemon file
set(    DAEMON_INC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../message_queue_lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../boost_logger_lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc
    )

# add executable
add_executable(daemon_app ${DAEMON_SRC})

# add compiler options for daemon
target_compile_options(daemon_app PUBLIC -std=c++17)

# add include files
target_include_directories(daemon_app PRIVATE ${DAEMON_INC})

target_link_libraries(daemon_app PUBLIC -lrt -lpthread)
target_link_libraries(daemon_app PUBLIC Boost::log_setup Boost::log pthread BoostLogger_lib_static MQ_lib_static)

install(TARGETS daemon_app)