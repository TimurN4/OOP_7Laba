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
    src/NPCManager.cpp  
)

# cmake_minimum_required(VERSION 3.1)

# project(NPCSystem)

# include_directories(include)

# file(GLOB SRC_FILES src/*.cpp)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
# )
# FetchContent_MakeAvailable(googletest)

# enable_testing()

# add_executable(NPCSystemTests tests/test.cpp ${SRC_FILES})

# target_link_libraries(NPCSystemTests gtest_main)

# add_test(NAME NPCSystemTests COMMAND NPCSystemTests)