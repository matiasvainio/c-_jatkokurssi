cmake_minimum_required(VERSION 3.13)
project(miniprojekti_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(miniprojekti_4 straight.c)
target_link_libraries(miniprojekti_4 m)