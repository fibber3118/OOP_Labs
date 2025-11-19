#include "Strategy.h"
#include "Strategy_Factory.h"
#include <string>

#ifndef LAB_2_TFT_H
#define LAB_2_TFT_H


class TFT : public Strategy {
public:
    Move next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) override;
};


#endif //LAB_2_TFT_H
