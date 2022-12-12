cmake_minimum_required(VERSION 3.23)
project(game9)

set(CMAKE_CXX_STANDARD 20)

set(NO_CONSOLE_FLAGS ", -Wl,--subsystem,windows")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fexceptions -static -static-libgcc -static-libstdc++ -g -static-libgcc -static-libstdc++ -L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}${NO_CONSOLE_FLAGS}" )
if (DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif(DEBUG)

add_executable(game9 main.cpp
        src/game_objects/Building.h
        src/game_objects/Money.cpp
        src/game_objects/Money.h
        src/game_objects/MainBuilding.cpp
        src/game_objects/MainBuilding.h
        src/game_objects/Button.cpp
        src/game_objects/Button.h
        src/game_objects/SideBuilding.cpp
        src/game_objects/SideBuilding.h
        src/utils/common.h
        res/icon.png
        src/actions/Actions.h
        src/actions/Actions.cpp
        src/game_objects/BuildingsList.cpp
        src/game_objects/BuildingsList.h
        src/utils/Saves.cpp
        src/utils/Saves.h
        src/menu/Gameplay.cpp
        src/menu/Gameplay.h
        src/menu/MainMenu.cpp
        src/menu/MainMenu.h
        src/menu/MenuOption.h
        src/menu/SettingsMenu.cpp
        src/menu/SettingsMenu.h
        src/menu/CreditsMenu.cpp
        src/menu/CreditsMenu.h
        src/menu_elements/TextFrame.cpp
        src/menu_elements/TextFrame.h
        src/menu_elements/SelectionForm.cpp
        src/menu_elements/SelectionForm.h
        src/utils/Cmd.cpp
        src/utils/Cmd.h
        src/menu_elements/RadioButton.cpp
        src/menu_elements/RadioButton.h
        src/actions.h
        src/game_objects.h
        src/menu.h
        src/menu_elements.h
        src/utils.h)

find_package(raylib CONFIG REQUIRED)
target_include_directories(game9 PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(game9 PRIVATE ${raylib_LIBRARIES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()
