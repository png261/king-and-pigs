cmake_minimum_required(VERSION 3.14)

# ---- Project ----

project(king-and-pigs LANGUAGES CXX)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
        )
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/CPM.cmake)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD_SHARED_LIBS" FORCE)
SET(BUILD_STATIC_LIBS ON CACHE BOOL "BUILD_STATIC_LIBS" FORCE)
SET(POSITION_INDEPENDENT_CODE ON CACHE BOOL "POSITION_INDEPENDENT_CODE" FORCE)

set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL2_IMAGE_SKIP_INSTALL_TARGETS ON CACHE BOOL "" FORCE)
set(SDL2_MIXER_SKIP_INSTALL_TARGETS ON CACHE BOOL "" FORCE)
set(SDL2_TTF_SKIP_INSTALL_TARGETS ON CACHE BOOL "" FORCE)

# SDL2
CPMAddPackage(
        NAME SDL2
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG release-2.26.2
        OPTIONS
        "SDL2_DISABLE_INSTALL ON"
        "SDL_SHARED OFF"
        "SDL_STATIC ON"
        "SDL_STATIC_PIC ON"
        "SDL_WERROR OFF"
)

find_package(SDL2 REQUIRED)
if (SDL2_ADDED)
    file(GLOB SDL_HEADERS "${SDL_SOURCE_DIR}/include/*.h")

    # Create a target that copies headers at build time, when they change
    add_custom_target(sdl_copy_headers_in_build_dir
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${SDL_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/SDLHeaders/SDL2"
            DEPENDS ${SDL_HEADERS})

    # Make SDL depend from it
    add_dependencies(SDL2-static sdl_copy_headers_in_build_dir)

    # And add the directory where headers have been copied as an interface include dir
    target_include_directories(SDL2-static INTERFACE "${CMAKE_BINARY_DIR}/SDLHeaders")

    set (SDL2_INCLUDE_DIR ${SDL2_SOURCE_DIR}/include)
endif()
include_directories(${SDL2_INCLUDE_DIR})

# SDL_ttf
CPMAddPackage(GITHUB_REPOSITORY libsdl-org/SDL_ttf
        GIT_TAG release-2.20.1
        OPTIONS
        "SDL2TTF_INSTALL OFF"
        "SDL2TTF_BUILD_SHARED_LIBS OFF"
        "SDL2TTF_VENDORED ON"
        "SDL2TTF_SAMPLES OFF"
) 
find_package(SDL_ttf REQUIRED)
include_directories(${SDL_ttf_SOURCE_DIR})

# SDL_image
CPMAddPackage(GITHUB_REPOSITORY libsdl-org/SDL_image
        GIT_TAG release-2.6.2
        OPTIONS
        "SDL2IMAGE_INSTALL OFF"
        "SDL2IMAGE_SAMPLES OFF"
        "SDL2IMAGE_VENDORED ON"
        "SDL2IMAGE_BUILD_SHARED_LIBS OFF"
)
find_package(SDL_image REQUIRED)
include_directories(${SDL_image_SOURCE_DIR})


## SDL_mixer
CPMAddPackage(GITHUB_REPOSITORY libsdl-org/SDL_mixer
        GIT_TAG release-2.6.2
        OPTIONS
        "SDL2MIXER_INSTALL OFF"
        "SDL2MIXER_VENDORED ON"
        "SDL2MIXER_SAMPLES OFF"
        "SDL2MIXER_BUILD_SHARED_LIBS OFF"
)
find_package(SDL_mixer REQUIRED)
include_directories(${SDL_mixer_SOURCE_DIR}/include)

CPMAddPackage(
    NAME box2d
    GIT_TAG v2.4.1 
    GITHUB_REPOSITORY erincatto/box2d
    OPTIONS 
    ${COMMON_CPM_OPTIONS}
    "BOX2D_BUILD_TESTBED OFF"
    "BOX2D_BUILD_UNIT_TESTS OFF"
    ) 

CPMAddPackage(
    NAME jsoncpp
    GIT_TAG 1.9.5 
    GITHUB_REPOSITORY open-source-parsers/jsoncpp
    OPTIONS 
    ${COMMON_CPM_OPTIONS}
    "JSONCPP_WITH_POST_BUILD_UNITTEST OFF"
    "JSONCPP_WITH_TESTS OFF"
    ) 

CPMAddPackage(
    NAME tinyxml2
    GIT_TAG 9.0.0
    GITHUB_REPOSITORY leethomason/tinyxml2
    OPTIONS 
    ${COMMON_CPM_OPTIONS}
    "tinyxml2_BUILD_TESTING OFF"
    ) 

# ---- Create executable ----
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${sources} ${headers} )

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    # SDL2
    SDL2-static 
    SDL2_image
    SDL2_image
    SDL2_mixer
    SDL2_ttf
    box2d
    jsoncpp
    tinyxml2
    )


