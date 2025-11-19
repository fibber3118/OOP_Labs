#include "Friendly_Strategy.h"
#include "Strategy_Factory.h"
#include <string>


Move Friendly_Strategy::next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) {
    return Move::C;
}

namespace {
    Strategy* create() {
        return new Friendly_Strategy;
    }
    bool crt = FactoryStrategy::getInstance()->register_strategy("Friendly", create);
}
