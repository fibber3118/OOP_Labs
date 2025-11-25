#include "Angry_Strategy.h"


Move Angry_Strategy::next_Move(int strategy_number, const std::vector<std::vector<Move>> &history) {
    return Move::D;
}

std::string Angry_Strategy::getName() {
    return "Angry";
}


namespace {
    Strategy* create() {
        return new Angry_Strategy;
    }
    bool crt = FactoryStrategy::getInstance()->register_strategy("Angry", create);
}