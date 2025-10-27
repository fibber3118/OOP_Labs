cmake_minimum_required(VERSION 3.10)

project(Lab_0 CXX)

find_package(GTest REQUIRED)

add_executable(Lab_0
        main.cpp
        csv_parser.cpp
        Words.cpp
)


add_executable(Lab_0_Tests
        test.cpp
        csv_parser.cpp
        Words.cpp
)

target_link_libraries(Lab_0_Tests
        GTest::gtest_main
)

include(CTest)
add_test(NAME GTest_Tests COMMAND Lab_0_Tests)