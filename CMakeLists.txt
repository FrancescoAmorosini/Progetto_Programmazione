cmake_minimum_required(VERSION 3.5)
project(Progetto_Programmazione)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(SOURCE_FILES main.cpp GameCharacter.cpp GameCharacter.h PlayableCharacter.cpp PlayableCharacter.h Orb.cpp Orb.cpp
        Orb.h Weapon.cpp Weapon.h RNG.h Chest.cpp Chest.h Tile.h Map.cpp Map.h RangeException.h CharacterFactory.cpp
        CharacterFactory.h DrawableObject.h Enemy.cpp Enemy.h GameLevel.h GameLevel.cpp Wall.h LevelCreator.cpp
        LevelCreator.h Spell.h Spell.cpp Heart.h RNG.cpp RNG.h LevelDrawer.cpp WeaponFactory.cpp WeaponFactory.h
        Strategy.cpp Observer.h Subject.h Strategy.h)
add_executable(Progetto_Programmazione ${SOURCE_FILES})

#Linking Googletest
add_library(core ${SOURCE_FILES})
target_link_libraries(Progetto_Programmazione core)

#SFML directory includes
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH}})
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Progetto_Programmazione ${SFML_LIBRARIES})
endif()
