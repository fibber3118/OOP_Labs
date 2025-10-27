#include <iostream>
#include <string>
#include <fstream>
#include "Words.h"

int Words::check_end(char symbol) {
    return symbol == '.' || symbol == ',' || symbol == ' ' || symbol == '!' || symbol == '?' || symbol == '"' ||
           symbol == ';' || symbol == ':' || symbol == '(' || symbol == ')';
}

int Words::read() {
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
