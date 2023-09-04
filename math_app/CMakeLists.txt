######################################################

# set source files
set(MATH_SRC
    math_app.cpp
    math_class.cpp)

# add libs dir to the math file
set(MATH_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../message_queue_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

# add executable
add_executable(math_app ${MATH_SRC})

# add compiler options for math application
target_compile_options(math_app PUBLIC -std=c++17)

# add include files
target_include_directories(math_app PRIVATE ${MATH_INC})

# link math with mq lib
target_link_libraries(math_app PRIVATE MQ_lib_static)

install(TARGETS math_app)
######################################################