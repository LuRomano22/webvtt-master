cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

if (BUILD_LIBRARY AND (WIN32 OR WIN64 OR MSVC))
  add_library(libwebvttxx OBJECT
          abstract_parser.cpp
          file_parser.cpp)
else (BUILD_LIBRARY AND (WIN32 OR WIN64 OR MSVC))
  add_library(libwebvttxx STATIC
          abstract_parser.cpp
          file_parser.cpp)
endif (BUILD_LIBRARY AND (WIN32 OR WIN64 OR MSVC))

target_include_directories(libwebvttxx PUBLIC
        "${PROJECT_SOURCE_DIR}/include")


# prevent the output file from being named something like "liblibwebvttxx.a"
set_target_properties(libwebvttxx PROPERTIES PREFIX "")