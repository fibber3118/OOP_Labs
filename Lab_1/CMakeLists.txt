cmake_minimum_required(VERSION 3.10)
project(Lab_1 CXX)

#set(CMAKE_CXX_STANDARD 14)

find_package(GTest CONFIG REQUIRED)

add_executable(Lab_1
        main.cpp
        BitArray.cpp
        BitArray.h)

add_executable(Lab_1_test
        bit_array_test.cpp
        BitArray.cpp
        BitArray.h)

target_link_libraries(Lab_1_test
        GTest::gtest_main
)

include(CTest)
add_test(NAME run_tests COMMAND Lab_1_test)
