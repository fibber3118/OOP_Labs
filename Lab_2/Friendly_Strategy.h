#include "Strategy.h"

#ifndef LAB_2_FRIENDLY_STRATEGY_H
#define LAB_2_FRIENDLY_STRATEGY_H


class Friendly_Strategy : public Strategy {
public:
    Move next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) override;

};


#endif //LAB_2_FRIENDLY_STRATEGY_H
