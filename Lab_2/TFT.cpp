#include "TFT.h"

Move TFT::next_Move(int strategy_number, const std::vector<std::vector<Move> > &history) {
    if (history.size() == 0) {
        return Move::C;
    }
    std::vector<Move> last_step = history[history.size() - 1];
    for (int i = 0; i < 3; i++) {
        if (last_step[i] == Move::C && i != strategy_number) {
            return Move::C;
        }
    }
    return Move::D;
}

namespace {
    Strategy* create() {
        return new TFT;
    }
    bool crt = FactoryStrategy::getInstance()->register_strategy("TFT", create);
}