# Written by Uglješa Lukešević & other contributors
# Licensed under GNU GPL-3.0
# Written for project, codename: grader
# github.com/ukicomputers/grader

cmake_minimum_required(VERSION 3.12)
project(grader-testcase)

set(CMAKE_CXX_STANDARD 17)

find_package(grader REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ukicomputers::grader)