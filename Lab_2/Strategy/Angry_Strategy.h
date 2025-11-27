#include "../src/Strategy.h"
#include "../src/Strategy_Factory.h"
#include <string>

#ifndef LAB_2_ANGRY_STRATEGY_H
#define LAB_2_ANGRY_STRATEGY_H


class Angry_Strategy : public Strategy {
public:
    Move next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) override;
};


#endif //LAB_2_ANGRY_STRATEGY_H
