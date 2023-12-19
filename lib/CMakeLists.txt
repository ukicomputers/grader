# Written by Uglješa Lukešević & other contributors
# Licensed under GNU GPL-3.0
# Written for project, codename: grader
# github.com/ukicomputers/grader

cmake_minimum_required(VERSION 3.12)
project(grader)

set(CMAKE_CXX_STANDARD 17)
add_library(grader src/grader.cpp)

target_include_directories(grader PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS grader
    EXPORT graderTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT graderTargets
    FILE graderTargets.cmake
    NAMESPACE ukicomputers::
    DESTINATION lib/cmake/grader
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    graderConfigVersion.cmake
    VERSION 1.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/graderConfig.cmake.in
    graderConfig.cmake
    INSTALL_DESTINATION lib/cmake/grader
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/graderConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/graderConfigVersion.cmake
    DESTINATION lib/cmake/grader
)