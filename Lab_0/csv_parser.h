

#ifndef LAB_0_CSV_PARSER_H
#define LAB_0_CSV_PARSER_H
class Words {
public:
    std::string word;
    std::ifstream infile;
    std::string str;
    int pos = 0;

    int read();
private:
    int check_end(char symbol);
};

int calc_words(std::string in, std::string out);
#endif //LAB_0_CSV_PARSER_H