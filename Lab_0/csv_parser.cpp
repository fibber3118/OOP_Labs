#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

class Words {
public:
    std::string word;
    std::ifstream infile;
    std::string str;
    int pos = 0;

    int read() {
        word = "";
        while (pos >= str.size()) {
            if (!std::getline(infile, str)) {
                return 1;
            }
            str.push_back(' ');
            pos = 0;
        }
        while (pos < str.size() && check_end(str[pos])) {
            pos++;
            if (pos >= str.size()) {
                return read();
            }
        }
        if (pos >= str.size()) {
            return 1;
        }
        while (pos < str.size() && !check_end(str[pos])) {
            word += std::tolower(str[pos]);
            pos++;
        }
        return 0;
    }

private:
    int check_end(char symbol) {
        return symbol == '.' || symbol == ',' || symbol == ' ' || symbol == '!' || symbol == '?' || symbol == '"' ||
            symbol == ';' || symbol == ':' || symbol == '('|| symbol == ')';
    }
};

struct Stats {
    std::string word;
    int count;
    float frequency;
};

int compare(Stats& a, Stats& b) {
    return a.count > b.count;
}

int calc_words(std::string in, std::string out) {
    Words Word;
    Word.infile.open(in);
    std::ofstream outfile(out);
    if (!Word.infile.is_open() || !outfile.is_open()) {
        return 2;
    }
    std::map<std::string, int> count_word;
    int count = 0;
    while (!Word.read()) {
        count++;
        count_word[Word.word]++;
    }
    std::vector<Stats> result;
    for (auto &pair: count_word) {
        Stats unit;
        unit.word = pair.first;
        unit.count = pair.second;
        unit.frequency = ((int)(((float)unit.count / (float)count) * 10000))/100.0;
        result.push_back(unit);
    }
    sort(result.begin(), result.end(), compare);
    for (int i = 0; i < result.size(); i++) {
        outfile << result[i].word << ',' << result[i].count << ',' << result[i].frequency << std::endl;
    }
    outfile.close();
    Word.infile.close();
    return 0;
}
