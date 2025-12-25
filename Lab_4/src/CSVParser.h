#ifndef LAB_4_CSVPARSER_H
#define LAB_4_CSVPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <utility>
#include "Iterator.h"

template <typename... Args>
class CSVParser {
    friend class Iterator<Args...>;

public:
    CSVParser(std::istream& input, size_t skip = 0, char col_sep = ',', char quote = '"')
        : is(input), skip_lines(skip), column_delimiter(col_sep), quote_char(quote) {}

    Iterator<Args...> begin() { return Iterator<Args...>(*this, false); }
    Iterator<Args...> end() { return Iterator<Args...>(); }

private:
    std::istream& is;
    size_t skip_lines;
    char column_delimiter;
    char quote_char;
};

#endif