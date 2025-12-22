#include "../src/Strategy.h"
#include "../src/Strategy_Factory.h"
#include <random>
#ifndef LAB_2_TFT_WITH_RANDOM_H
#define LAB_2_TFT_WITH_RANDOM_H


class TFT_With_Random : public Strategy{
    Move next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) override;
};


#endif //LAB_2_TFT_WITH_RANDOM_H