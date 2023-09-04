######################################################
# create static and shared library

cmake_minimum_required(VERSION 3.22)

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
        set(Boost_INCLUDE_DIR "${BOOST_ROOT}/boost")
        set(Boost_LIBRARY_DIRS "${BOOST_ROOT}/lib")
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

# set boost logger soruce files
set (   LOGGER_SRC
        logger.cpp
    )

# add static lib
add_library(BoostLogger_lib_static STATIC ${LOGGER_SRC})

# add shared lib
add_library(BoostLogger_lib_shared SHARED ${LOGGER_SRC})

# link with needed libs for static library
target_link_libraries(BoostLogger_lib_static PUBLIC Boost::log_setup Boost::log pthread)

# link with needed libs for shared library
target_link_libraries(BoostLogger_lib_shared PUBLIC Boost::log_setup Boost::log pthread)

######################################################