file (GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES} "Controller.cpp" "../include/Window.h" "Window.cpp" "../include/Menu.h" "Menu.cpp" "Resources.cpp" "../include/Board.h" "Board.cpp" "../include/BaseButton.h" "../include/QuitButton.h"  "QuitButton.cpp" "../include/PlayButton.h" "PlayButton.cpp" "../include/Setting.h" "Setting.cpp" "../include/TutorialButton.h" "TutorialButton.cpp" "../include/Goal.h" "Goal.cpp" "../include/MultiplayerButton.h" "MultiplayerButton.cpp" "../include/PlayerButton.h" "PlayerButton.cpp" "../include/MovingObject.h" "MovingObject.cpp" "../include/Player.h" "Player.cpp" "../include/Keyboard.h")


