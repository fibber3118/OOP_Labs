#ifndef LAB_4_TUPLE_PRINT_H
#define LAB_4_TUPLE_PRINT_H
#include <iostream>
#include <tuple>


template<typename Tuple, std::size_t Index, std::size_t Size>
struct TuplePrinter {
    template<typename Ch, typename Tr>
    static void print(std::basic_ostream<Ch, Tr> &os, const Tuple &t) {
        os << std::get < Index > (t);
        if (Index < Size - 1) {
            os << ", ";
        }
        TuplePrinter<Tuple, Index + 1, Size>::print(os, t);
    }
};


template<typename Tuple, std::size_t Size>
struct TuplePrinter<Tuple, Size, Size> {
    template<typename Ch, typename Tr>
    static void print(std::basic_ostream<Ch, Tr> &os, const Tuple &t) {
    }
};

template<typename Ch, typename Tr, typename... Args>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &t)
    -> std::basic_ostream<Ch, Tr> & {
    TuplePrinter<decltype(t), 0, sizeof...(Args)>::print(os, t);
    return os;
}

#endif //LAB_4_TUPLE_PRINT_H