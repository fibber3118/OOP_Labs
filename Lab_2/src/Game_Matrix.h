#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "Strategy.h"
#ifndef LAB_2_GAME_MATRIX_H
#define LAB_2_GAME_MATRIX_H
#include <vector>


class Game_Matrix {
public:
    std::vector<int> results;

    Game_Matrix(const std::string filename);

    void get_result(std::vector<Move>& choices);

private:
    std::vector<std::vector<int> > matrix;
    int get_index(std::vector<Move>& choices);
};


#endif //LAB_2_GAME_MATRIX_H
