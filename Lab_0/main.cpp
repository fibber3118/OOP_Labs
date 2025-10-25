#include <iostream>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
#include "csv_parser.h"

std::vector<std::string> read_words(std::string in) {
    std::vector<std::string> word;
    Words token;
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

TEST(parser, test_p) {
    std::vector<std::string> good_res = {
        "hyphenated-word,3,18.75",
        "test,3,18.75",
        "word,3,18.75",
        "comma,1,6.25",
        "list,1,6.25",
        "parenthetical,1,6.25",
        "quoted,1,6.25",
        "remarks,1,6.25",
        "separated,1,6.25",
        "words,1,6.25"
    };
    std::string result;
    calc_words("in2.txt", "out.csv");
    std::ifstream res("out.csv");
    ASSERT_EQ(res.is_open(), 1) << "Не удалось открыть out.csv";
    int i = 0;
    while (std::getline(res, result)) {
        ASSERT_LT(i, good_res.size()) << "Строк больше, чем ожидалось";
        ASSERT_EQ(result, good_res[i]) << "Ошибка в строке " << i + 1  << "ожидалось " << good_res[i] << " пришло " << result<< std::endl;
        i++;
    }
    res.close();

}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
