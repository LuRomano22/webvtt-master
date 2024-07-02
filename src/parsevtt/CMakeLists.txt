cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

add_executable(parsevtt parsevtt_main.c)

target_include_directories(parsevtt PUBLIC
        "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(parsevtt
        libwebvtt)
