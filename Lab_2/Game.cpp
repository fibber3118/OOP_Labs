#include "Game.h"
#include <iostream>
#include "Game_Matrix.h"
#include "Strategy_Factory.h"
#include "Strategy.h"

std::vector<std::string> processing_input(int argc, char *arg[], std::string &mode, std::string& step) {
    if (argc < 3) {
        throw std::invalid_argument("Передайте минимум 3 стратегии");
    }
    std::vector<std::string> strategy_list;
    bool mode_flag = 1;
    for (int i = 1; i < argc; i++) {
        std::string current_arg = arg[i];
        if (current_arg.rfind("--mode=", 0) == 0) {
            mode = current_arg.substr(7);
            mode_flag = 0;
        } else if (current_arg.rfind("--step=", 0) == 0) {
            step = current_arg.substr(7);
        } else {
            strategy_list.push_back(current_arg);
        }
    }
    if (mode_flag) {
        if (strategy_list.size() == 3) {
            mode = "detailed";
        } else {
            mode = "tournament";
        }
    }
    return strategy_list;
}

std::vector<std::unique_ptr<Strategy> > create_players(std::vector<std::string> &strategy_list) {
    std::vector<std::unique_ptr<Strategy> > players;
    for (int i = 0; i < strategy_list.size(); i++) {
        auto s = FactoryStrategy::getInstance()->create_strategy(strategy_list[i]);
        if (s == nullptr) {
            throw std::invalid_argument("Неверное название стратегии");
        }
        players.push_back(std::move(s));
    }
    return players;
}

void match(std::vector<std::unique_ptr<Strategy> > &players, std::vector<int> &score, bool detailed,
           int count_step) {
    Game_Matrix matrix;
    std::vector<std::vector<Move> > history;
    std::vector<Move> choices(3);
    for (int i = 0; i < count_step; i++) {
        for (int q = 0; q < 3; q++) {
            choices[q] = players[q]->next_Move(q, history);
        }
        history.push_back(choices);
        matrix.get_result(choices);
        for (int q = 0; q < 3; q++) {
            score[q] += matrix.results[q];
        }
        std::cout << score[0] << ' ' << score[1] << ' ' << score[2] << ' ' << std::endl;
        if (detailed) {
            std::cin.get();
        }
    }
}

void game(int argc, char *arg[]) {
    std::vector<std::unique_ptr<Strategy> > players;
    std::string mode;
    std::string step;
    try {
        std::vector<std::string> strategy_list = processing_input(argc, arg, mode, step);
        players = create_players(strategy_list);
    } catch (std::invalid_argument &err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    int count_step = std::stoi(step);
    std::vector<int> score(3);
    match(players, score, mode == "detailed", count_step);
}
