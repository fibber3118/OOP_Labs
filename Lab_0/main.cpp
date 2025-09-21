#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

class words {
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
        return symbol == '.' || symbol == ',' || symbol == ' ' || symbol == '!' || symbol == '?';
    }
};

struct stats {
    std::string word;
    int count;
    float frequency;
};

int compair(stats& a, stats& b) {
    return a.count > b.count;
}


int main(int count_arg, char *arg[]) {
    using namespace std;
    if (count_arg != 3) {
        cout << "Передайте in.txt out.csv" << endl;
        return 1;
    }
    words word;
    word.infile.open(arg[1]);
    ofstream outfile(arg[2]);
    if (!word.infile.is_open() || !outfile.is_open()) {
        return 2;
    }
    map<string, int> count_word;
    int count = 0;
    while (!word.read()) {
        count++;
        count_word[word.word]++;
    }
    vector<stats> result;
    for (auto &pair: count_word) {
        stats unit;
        unit.word = pair.first;
        unit.count = pair.second;
        unit.frequency = ((float)unit.count / (float)count) * 100;
        result.push_back(unit);
    }
    sort(result.begin(), result.end(), compair);
    for (int i = 0; i < result.size(); i++) {
        outfile << result[i].word << ',' << result[i].count << ',' << result[i].frequency << endl;
    }
    return 0;
}
