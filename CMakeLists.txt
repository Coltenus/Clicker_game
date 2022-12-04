cmake_minimum_required(VERSION 3.23)
project(game9)

set(CMAKE_CXX_STANDARD 20)

set(NO_CONSOLE_FLAGS ", -Wl,--subsystem,windows")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fexceptions -static -static-libgcc -static-libstdc++ -g -static-libgcc -static-libstdc++ -L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}${NO_CONSOLE_FLAGS}" )
if (DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif(DEBUG)

add_executable(game9 main.cpp src/Building.h src/Money.cpp src/Money.h src/MainBuilding.cpp src/MainBuilding.h src/Button.cpp src/Button.h src/SideBuilding.cpp src/SideBuilding.h src/common.h res/icon.png src/Actions.h src/Actions.cpp src/BuildingsList.cpp src/BuildingsList.h src/Saves.cpp src/Saves.h src/Gameplay.cpp src/Gameplay.h src/MainMenu.cpp src/MainMenu.h src/MenuOption.h)

find_package(raylib CONFIG REQUIRED)
target_include_directories(game9 PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(game9 PRIVATE ${raylib_LIBRARIES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()
