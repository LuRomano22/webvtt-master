cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(GTEST_ROOT ThirdParty/googletest-release-1.8.0)

add_subdirectory("googletest-release-1.10.0" EXCLUDE_FROM_ALL)
add_subdirectory("unit")
