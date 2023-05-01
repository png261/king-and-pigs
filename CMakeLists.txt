cmake_minimum_required(VERSION 3.21...3.25)

# ---- Project ----

project(king-and-pigs LANGUAGES CXX)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

add_compile_options(${PROJECT_NAME} PRIVATE "-Wall -Wextra -Wpedantic -Wshadow -Werror")


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# ---- Create executable ----

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${headers} ${sources})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(box2d REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(JsonCpp REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TFF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME} 
    SDL2::Main
    SDL2::Image
    SDL2::TTF
    SDL2::Mixer
    SDL2::GFX
    box2d::box2d
    tinyxml2::tinyxml2
    jsoncpp
)

