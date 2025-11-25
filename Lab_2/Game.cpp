#include "Game.h"
#include <iostream>
#include <algorithm>
#include "Game_Matrix.h"
#include "Strategy_Factory.h"
#include "Strategy.h"

std::vector<std::string> processing_input(int argc, char *arg[], std::string &mode, std::string &step,
                                          std::string &matrix_file) {
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
        } else if (current_arg.rfind("--matrix=", 0) == 0) {
            matrix_file = current_arg.substr(9);
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
            throw std::invalid_argument("Неверное название стратегии: " + strategy_list[i]);
        }
        players.push_back(std::move(s));
    }
    return players;
}

void match(std::vector<std::unique_ptr<Strategy> > &players, std::vector<int> &score, bool detailed,
           int count_step, Game_Matrix &matrix) {
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
        if (detailed) {
            std::cout << score[0] << ' ' << score[1] << ' ' << score[2];
            std::cin.get();
        } else if (!detailed && count_step < 20) {
            std::cout << score[0] << ' ' << score[1] << ' ' << score[2] << std::endl;
        }
    }
    std::cout << score[0] << ' ' << score[1] << ' ' << score[2] << std::endl;
}

struct StrategyScore {
    std::string name;
    int score;

    bool operator>(const StrategyScore &other) const {
        return score > other.score;
    }
};

void tournament(const std::vector<std::string> &strategy_list, int count_step, Game_Matrix &matrix) {
    if (strategy_list.size() < 3) {
        std::cerr << "Ошибка: Для турнира требуется минимум 3 стратегии." << std::endl;
        return;
    }
    std::vector<int> total_scores(strategy_list.size(), 0);
    std::cout << "=== НАЧАЛО ТУРНИРА ===" << std::endl;
    for (size_t i = 0; i < strategy_list.size(); ++i) {
        for (size_t j = i + 1; j < strategy_list.size(); ++j) {
            for (size_t k = j + 1; k < strategy_list.size(); ++k) {
                std::vector<std::string> current_names = {strategy_list[i], strategy_list[j], strategy_list[k]};
                std::vector<int> match_score(3, 0);

                try {
                    auto players = create_players(current_names);
                    std::cout << "Матч: "
                            << strategy_list[i] << " vs "
                            << strategy_list[j] << " vs "
                            << strategy_list[k] << " -> ";

                    match(players, match_score, false, count_step, matrix);

                    std::cout << match_score[0] << " : " << match_score[1] << " : " << match_score[2] << std::endl;

                    total_scores[i] += match_score[0];
                    total_scores[j] += match_score[1];
                    total_scores[k] += match_score[2];
                } catch (const std::exception &e) {
                    std::cerr << "Ошибка при создании стратегий: " << e.what() << std::endl;
                    return;
                }
            }
        }
    }
    std::vector<StrategyScore> final_results;
    for (size_t i = 0; i < strategy_list.size(); ++i) {
        final_results.push_back({strategy_list[i], total_scores[i]});
    }
    std::sort(final_results.begin(), final_results.end(), [](const StrategyScore &a, const StrategyScore &b) {
        return a > b;
    });
    std::cout << "\nИтог" << std::endl;
    for (const auto &res: final_results) {
        std::cout << res.name << ": " << res.score << " очков" << std::endl;
    }
    std::cout << "Победитель: " << final_results[0].name << std::endl;
}

void game(int argc, char *arg[]) {
    std::string mode;
    std::string step = "10";
    std::string matrix_file = "";
    std::vector<std::string> strategy_list;

    try {
        strategy_list = processing_input(argc, arg, mode, step, matrix_file);
    } catch (std::invalid_argument &err) {
        std::cerr << "Ошибка: " << err.what() << std::endl;
        return;
    }

    int count_step = std::stoi(step);
    Game_Matrix matrix("");
    try {
        matrix = Game_Matrix(matrix_file);
    } catch (const std::exception &e) {
        std::cerr << "Ошибка матрицы: " << e.what() << std::endl;
        return;
    }

    if (mode == "tournament") {
        tournament(strategy_list, count_step, matrix);
    } else {
        if (strategy_list.size() != 3) {
            std::cerr << "Для режима " << mode << " требуется ровно 3 стратегии." << std::endl;
            return;
        }

        std::vector<std::unique_ptr<Strategy> > players;
        try {
            players = create_players(strategy_list);
        } catch (std::invalid_argument &err) {
            std::cerr << err.what() << std::endl;
            return;
        }

        std::vector<int> score(3, 0);
        match(players, score, mode == "detailed", count_step, matrix);
        std::cout << "Результат: " << score[0] << ' ' << score[1] << ' ' << score[2] << std::endl;
    }
}
