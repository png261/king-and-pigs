# ---- Add source files ----
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# ---- Create executable ----
if(WIN32)
    add_executable(${PROJECT_NAME} ${sources} ${headers} "${PROJECT_SOURCE_DIR}/data/icon/icon.rc")
else()
    add_executable(${PROJECT_NAME} ${sources} ${headers})
endif(WIN32)

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
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC -static -static-libgcc -static-libstdc++ -mwindows)
    add_definitions("-DSDL_MAIN_HANDLED") # fix Undefined reference to 'WinMain'
endif(WIN32)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
