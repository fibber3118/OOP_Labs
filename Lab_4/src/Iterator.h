#ifndef LAB_4_ITERATOR_H
#define LAB_4_ITERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <utility>


template <typename... Args> class CSVParser;

template <typename... Args>
class Iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::tuple<Args...>;
    using pointer = const std::tuple<Args...>*;
    using reference = const std::tuple<Args...>&;

    Iterator() : parser(nullptr), is_end(true) {}

    Iterator(CSVParser<Args...>& parser, bool is_end)
        : parser(&parser), is_end(is_end) {
        if (!is_end) {
            skip_initial_lines();
            read_next();
        }
    }

    reference operator*() const { return current_row; }
    pointer operator->() const { return &current_row; }

    Iterator& operator++() {
        read_next();
        return *this;
    }

    bool operator==(const Iterator& other) const {
        if (is_end && other.is_end) return true;
        return is_end == other.is_end && parser == other.parser;
    }

    bool operator!=(const Iterator& other) const { return !(*this == other); }

private:
    CSVParser<Args...>* parser;
    std::tuple<Args...> current_row;
    bool is_end;

    void skip_initial_lines() {
        for (size_t i = 0; i < parser->skip_lines; i++) {
            std::vector<std::string> s;
            if (!read_raw(s)) {
                is_end = true;
                break;
            }
        }
    }

    bool read_raw(std::vector<std::string>& fields) {
        fields.clear();
        std::string field;
        bool in_quotes = false;
        char ch;
        while (parser->is.get(ch)) {
            if (ch == parser->quote_char) {
                if (in_quotes && parser->is.peek() == parser->quote_char) {
                    field += (char)parser->is.get();
                } else {
                    in_quotes = !in_quotes;
                }
            } else if (ch == parser->column_delimiter && !in_quotes) {
                fields.push_back(field);
                field.clear();
            } else if (ch == '\n' && !in_quotes) {
                fields.push_back(field);
                return true;
            } else if (ch == '\r' && !in_quotes) {
                if (parser->is.peek() == '\n') parser->is.get();
                fields.push_back(field);
                return true;
            } else {
                field += ch;
            }
        }
        if (!field.empty() || !fields.empty()) {
            fields.push_back(field);
            return true;
        }
        return false;
    }

    void read_next() {
        std::vector<std::string> fields;
        if (read_raw(fields)) {
            parse_fields(fields, current_row, std::index_sequence_for<Args...>{});
        } else {
            is_end = true;
        }
    }

    template <typename T>
    void convert(const std::string& s, T& value) {
        std::stringstream ss(s);
        ss >> value;
    }

    void convert(const std::string& s, std::string& value) {
        value = s;
    }

    template <size_t... Is>
    void parse_fields(const std::vector<std::string>& fields, std::tuple<Args...>& t, std::index_sequence<Is...>) {
        size_t n = 0;
        ((n < fields.size() ? convert(fields[n++], std::get<Is>(t)) : void()), ...);
    }
};

#endif