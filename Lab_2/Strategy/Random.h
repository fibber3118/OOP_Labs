#include "../src/Strategy.h"
#include "../src/Strategy_Factory.h"
#include <random>

#ifndef LAB_2_RANDOM_H
#define LAB_2_RANDOM_H


class Random : public Strategy {
    Move next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) override;
};


#endif //LAB_2_RANDOM_H
