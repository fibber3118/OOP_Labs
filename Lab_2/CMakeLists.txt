cmake_minimum_required(VERSION 4.0)
project(Lab_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package(GTest CONFIG REQUIRED)

add_executable(Lab_2
        src/main.cpp
        src/Strategy_Factory.h
        src/Strategy.h
        Strategy/Friendly_Strategy.cpp
        Strategy/Friendly_Strategy.h
        Strategy/Angry_Strategy.cpp
        Strategy/Angry_Strategy.h
        src/Game.cpp
        src/Game.h
        src/Game_Matrix.cpp
        src/Game_Matrix.h
        Strategy/TFT.cpp
        Strategy/TFT.h
        Strategy/Random.cpp
        Strategy/Random.h
        Strategy/TFT_With_Random.cpp
        Strategy/TFT_With_Random.h
)


add_executable(Lab_2_test
        src/test.cpp
        src/Strategy_Factory.h
        src/Strategy.h
        Strategy/Friendly_Strategy.cpp
        Strategy/Friendly_Strategy.h
        Strategy/Angry_Strategy.cpp
        Strategy/Angry_Strategy.h
        src/Game.cpp
        src/Game.h
        src/Game_Matrix.cpp
        src/Game_Matrix.h
        Strategy/TFT.cpp
        Strategy/TFT.h
        Strategy/Random.cpp
        Strategy/Random.h
        Strategy/TFT_With_Random.cpp
        Strategy/TFT_With_Random.h
)

target_link_libraries(Lab_2_test
        GTest::gtest_main
)

include(CTest)
add_test(NAME run_tests COMMAND Lab_2_test)