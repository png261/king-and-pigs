# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(CPM)

# SDL2
CPMAddPackage(
    NAME SDL2
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-2.26.2
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "BUILD_STATIC_LIBS ON"
            "POSITION_INDEPENDENT_CODE ON"
            "SDL2_DISABLE_INSTALL ON"
            "SDL_SHARED OFF"
            "SDL_STATIC ON"
            "SDL_STATIC_PIC ON"
            "SDL_WERROR OFF"
)

# SDL_image
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_image
    GIT_TAG release-2.6.2
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "BUILD_STATIC_LIBS ON"
            "POSITION_INDEPENDENT_CODE ON"
            "SDL2IMAGE_INSTALL OFF"
            "SDL2IMAGE_SAMPLES OFF"
            "SDL2IMAGE_VENDORED ON"
            "SDL2IMAGE_BUILD_SHARED_LIBS OFF"
)

# SDL_mixer
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_mixer
    GIT_TAG release-2.6.2
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "BUILD_STATIC_LIBS ON"
            "POSITION_INDEPENDENT_CODE ON"
            "SDL2MIXER_INSTALL OFF"
            "SDL2MIXER_VENDORED ON"
            "SDL2MIXER_SAMPLES OFF"
            "SDL2MIXER_BUILD_SHARED_LIBS OFF"
)

# SDL_ttf
CPMAddPackage(
    GITHUB_REPOSITORY libsdl-org/SDL_ttf
    GIT_TAG release-2.20.1
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "BUILD_STATIC_LIBS ON"
            "POSITION_INDEPENDENT_CODE ON"
            "SDL2TTF_INSTALL OFF"
            "SDL2TTF_BUILD_SHARED_LIBS OFF"
            "SDL2TTF_VENDORED ON"
            "SDL2TTF_SAMPLES OFF"
)

# Box2D
CPMAddPackage(
    NAME box2d
    GIT_TAG v2.4.1
    GITHUB_REPOSITORY erincatto/box2d
    OPTIONS "BUILD_SHARED_LIBS OFF" "BUILD_STATIC_LIBS ON" "BOX2D_BUILD_TESTBED OFF"
            "BOX2D_BUILD_UNIT_TESTS OFF"
)

# nlohmann/json
CPMAddPackage(
    NAME nlohmann_json
    VERSION 3.10.4
    GITHUB_REPOSITORY nlohmann/json
    OPTIONS "BUILD_SHARED_LIBS OFF" "BUILD_STATIC_LIBS ON"
)

# TinyXML2
CPMAddPackage(
    NAME tinyxml2
    GIT_TAG 9.0.0
    GITHUB_REPOSITORY leethomason/tinyxml2
    OPTIONS "BUILD_SHARED_LIBS OFF" "BUILD_STATIC_LIBS ON" "POSITION_INDEPENDENT_CODE ON"
            "tinyxml2_BUILD_TESTING OFF"
)

# ---- Static libraries ----
# SDL2_gfx
add_subdirectory(SDL2_gfx)
