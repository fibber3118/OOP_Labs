#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "Words.h"


struct Word_data {
    std::string word;
    int count;
    float frequency;
};

int compare(Word_data& a, Word_data& b) {
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
    std::vector<Word_data> result;
    for (auto &pair: count_word) {
        Word_data unit;
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
