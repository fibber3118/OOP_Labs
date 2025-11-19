#include <vector>


#ifndef LAB_2_STRATEGY_H
#define LAB_2_STRATEGY_H


enum class Move{C, D};

class Strategy{
public:
    virtual Move next_Move(int strategy_number, const std::vector<std::vector<Move>>& history) = 0;
    virtual ~Strategy() = default;
};

#endif //LAB_2_STRATEGY_H