cmake_minimum_required(VERSION 3.10)

project(compiler)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(util)
add_subdirectory(test)
# add_executable(compiler compiler.c)
# target_link_libraries(compiler PRIVATE util)
