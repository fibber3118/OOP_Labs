#include "Random.h"

Move Random::next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>distrib(0, 1);
    bool move = distrib(gen);
    if (move == 1) {
        return Move::C;
    }
    return Move::D;
}



namespace {
    Strategy* create() {
        return new Random;
    }
    bool crt = FactoryStrategy::getInstance()->register_strategy("Random", create);
}