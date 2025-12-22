#include "TFT_With_Random.h"

Move TFT_With_Random::next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) {
    if (history.size() == 0) {
        return Move::C;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>distrib(0, 10);
    int move = distrib(gen);
    if (move == 0) {
        return Move::D;
    }
    if (move > 8) {
        return Move::C;
    }
    std::vector<Move> last_step = history[history.size() - 1];
    for (int i = 0; i < 3; i++) {
        if (last_step[i] == Move::D && i != strategy_number) {
            return Move::D;
        }
    }
    return Move::C;
}



namespace {
    Strategy* create() {
        return new TFT_With_Random;
    }
    bool crt = FactoryStrategy::getInstance()->register_strategy("Random_TFT", create);
}