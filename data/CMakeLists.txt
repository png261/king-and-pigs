set(CONFIG_FILE "data/config.json")
set(IMAGE_DIRECTORY "data/images/")
set(SOUND_DIRECTORY "data/sounds/")
set(FONT_DIRECTORY "data/fonts/")
set(LEVEL_DIRECTORY "data/levels/")
set(ICON_DIRECTORY "data/icon/")

set(GAME_DEBUG false)
set(GAME_WIDTH 1280)
set(GAME_HEIGHT 768)
set(GAME_TITLE ${PROJECT_NAME})

set(GAME_LEVELS "\"${LEVEL_DIRECTORY}level1.json\", \"${LEVEL_DIRECTORY}level2.json\"")

configure_file(${PROJECT_SOURCE_DIR}/${CONFIG_FILE}.in ${PROJECT_SOURCE_DIR}/${CONFIG_FILE})

configure_file(
    ${PROJECT_SOURCE_DIR}/source/CONSTANT.hpp.in ${PROJECT_SOURCE_DIR}/source/CONSTANT.hpp
)

set(DATA_ICO_ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.ico")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "/")
