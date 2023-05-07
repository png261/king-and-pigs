cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

project(
    king-and-pigs
    VERSION 1.0
    LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# --- Import tools ----

include(cmake/tools.cmake)

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

set(BUILD_SHARED_LIBS
    OFF
    CACHE BOOL "BUILD_SHARED_LIBS" FORCE
)
set(BUILD_STATIC_LIBS
    ON
    CACHE BOOL "BUILD_STATIC_LIBS" FORCE
)
set(POSITION_INDEPENDENT_CODE
    ON
    CACHE BOOL "POSITION_INDEPENDENT_CODE" FORCE
)

# SDL2
CPMAddPackage(
    NAME SDL2
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-2.26.2
    OPTIONS "SDL2_DISABLE_INSTALL ON" "SDL_SHARED OFF" "SDL_STATIC ON" "SDL_STATIC_PIC ON"
            "SDL_WERROR OFF"
)

# SDL_image
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_image
    GIT_TAG release-2.6.2
    OPTIONS "SDL2IMAGE_INSTALL OFF" "SDL2IMAGE_SAMPLES OFF" "SDL2IMAGE_VENDORED ON"
            "SDL2IMAGE_BUILD_SHARED_LIBS OFF"
)

# SDL_mixer
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_mixer
    GIT_TAG release-2.6.2
    OPTIONS "SDL2MIXER_INSTALL OFF" "SDL2MIXER_VENDORED ON" "SDL2MIXER_SAMPLES OFF"
            "SDL2MIXER_BUILD_SHARED_LIBS OFF"
)

# SDL_ttf
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_ttf
    GIT_TAG release-2.20.1
    OPTIONS "SDL2TTF_INSTALL OFF" "SDL2TTF_BUILD_SHARED_LIBS OFF" "SDL2TTF_VENDORED ON"
            "SDL2TTF_SAMPLES OFF"
)

# Box2D
CPMAddPackage(
    NAME box2d
    GIT_TAG v2.4.1
    GITHUB_REPOSITORY erincatto/box2d
    OPTIONS "BOX2D_BUILD_TESTBED OFF" "BOX2D_BUILD_UNIT_TESTS OFF"
)

# nlohmann/json
CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.10.4
  GITHUB_REPOSITORY nlohmann/json
)

# TinyXML2
CPMAddPackage(
    NAME tinyxml2
    GIT_TAG 9.0.0
    GITHUB_REPOSITORY leethomason/tinyxml2
    OPTIONS "tinyxml2_BUILD_TESTING OFF"
)

add_definitions("-DSDL_MAIN_HANDLED")

# ---- Add source files ----
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ---- Create executable ----
add_executable(${PROJECT_NAME} ${sources} ${headers})

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC SDL2-static
           SDL2_image
           SDL2_mixer
           SDL2_ttf
           box2d
           nlohmann_json::nlohmann_json
           tinyxml2
           -static 
           -static-libgcc 
           -static-libstdc++
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "assets")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/data/" DESTINATION "data")
install(DIRECTORY ${SDL2_INCLUDE_DIRS} DESTINATION "include")
install(FILES ${SDL2_LIBRARIES} DESTINATION "lib")

# ---- Create Installer ----
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "NSIS") # This will create a NSIS installer
set(CPACK_PACKAGE_NAME "King and Pigs")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ game")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "KingAndPigs")
set( CPACK_PACKAGE_NAME "KingAndPigs" )
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME};KingAndPigs")

include(CPack)
