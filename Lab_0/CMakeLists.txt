cmake_minimum_required(VERSION 3.10)

project(Lab_0 CXX)

find_package(GTest REQUIRED)

add_executable(Lab_0
        main.cpp
        csv_parser.cpp
)

target_link_libraries(Lab_0
        GTest::gtest_main
)