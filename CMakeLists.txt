cmake_minimum_required(VERSION 3.20)
project(servercalculator C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/)
add_executable(servercalculator main.c)
target_link_libraries(servercalculator pthread)