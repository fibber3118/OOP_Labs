#include <iostream>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
#include "csv_parser.h"

std::vector<std::string> read_words(std::string in) {
    std::vector<std::string> word;
    words token;
    token.infile.open(in);
    while (!token.read()) {
        word.push_back(token.word);
    }
    return word;
}

TEST(read_func, test1) {
    std::vector<std::string> good_res = {
        "hello",
        "world",
        "apple",
        "cube",
        "test",
        "words"
    };
    std::vector<std::string> result = read_words("in1.txt");

    ASSERT_EQ(good_res.size(), result.size()) << "Не совпадает количество слов";

    for (int i = 0; i < result.size(); i++) {
        ASSERT_EQ(good_res[i], result[i]) << "Не совпадение слова №" << i;
    }

}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
