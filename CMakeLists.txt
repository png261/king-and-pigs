cmake_minimum_required(VERSION 3.14...3.22)

project(KingAndPigs LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

set(AUTHOR_NAME "phuong nguyen")
set(AUTHOR_GITHUB "https://github.com/png261")
set(AUTHOR_GMAIL "nhphuong.code@gmail.com")
set(PROJECT_GITHUB_URL "https://github.com/png261/king-and-pigs")
set(PROJECT_SUMMARY "C++ game")
set(PROJECT_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(PROJECT_DESCRIPTION "${PROJECT_SOURCE_DIR}/README.md")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(useGoldLinker)

add_subdirectory(external)
add_subdirectory(data)
add_subdirectory(source)
add_subdirectory(packaging)
