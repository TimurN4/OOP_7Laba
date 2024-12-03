cmake_minimum_required(VERSION 3.10)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(BalagurFate3
    src/main.cpp
    src/NPC.cpp
    src/NPCFactory.cpp
    src/BattleVisitor.cpp
    src/Observer.cpp
)