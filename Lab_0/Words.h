//
// Created by evgeniy on 26.10.2025.
//

#ifndef LAB_0_WORDS_H
#define LAB_0_WORDS_H

class Words {
public:
    std::string word;
    std::ifstream infile;
    int read();
private:
    int check_end(char symbol);
    std::string str;
    int pos = 0;
};

#endif //LAB_0_WORDS_H