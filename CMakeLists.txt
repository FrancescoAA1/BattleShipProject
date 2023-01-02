cmake_minimum_required(VERSION 2.84)
set(CMAKE_CXX_STANDARD 11)
project(battaglia_navale)

include_directories(include)

add_library(Position src/Position.cpp)
add_library(AttackGrid src/AttackGrid.cpp)
add_library(DefenseUnit src/DefenseUnit.cpp)
add_library(DefenseMap src/DefenseMap.cpp)
add_library(Ship src/Ship.cpp)
add_library(Ironclad src/Ironclad.cpp)
add_library(SupportShip src/Supportship.cpp)
add_library(Submarine src/Submarine.cpp)
add_library(Player src/Player.cpp)
add_library(RobotPlayer src/RobotPlayer.cpp)
add_library(HumanPlayer src/HumanPlayer.cpp)
add_library(Move src/Move.cpp)
add_library(Game src/Game.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} Position AttackGrid DefenseUnit DefenseMap Ship Ironclad SupportShip Submarine Player RobotPlayer HumanPlayer Move Game)