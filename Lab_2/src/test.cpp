#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <gtest/gtest.h>
#include "Game.h"

class CoutRedirect {
private:
    std::stringstream& ss_;
    std::streambuf* old_cout_buffer_;

public:
    CoutRedirect(std::stringstream& stream)
        : ss_(stream), old_cout_buffer_(std::cout.rdbuf(ss_.rdbuf())) {}
    ~CoutRedirect() {
        std::cout.rdbuf(old_cout_buffer_);
    }
    CoutRedirect(const CoutRedirect&) = delete;
    CoutRedirect& operator=(const CoutRedirect&) = delete;
};

TEST(Game_Test, Test1) {
    char* arg[] = {"lab", "Friendly", "Friendly", "Friendly", "--step=1"};
    int argc = 5;
    std::stringstream out;
    CoutRedirect g_out(out);
    std::string good_out = "7 7 7";
    game(argc, arg);
    ASSERT_EQ(out.str(), good_out);
}