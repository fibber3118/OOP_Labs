#include "Game_Matrix.h"

#include <tuple>


Game_Matrix::Game_Matrix() {
    results.resize(3);
    matrix.resize(8);
    for (int i = 0; i < 8; i++) {
        matrix[i].resize(3);
    }
    matrix[0] = {7, 7, 7};
    matrix[1] = {3, 3, 9};
    matrix[2] = {3, 9, 3};
    matrix[3] = {0, 5, 5};
    matrix[4] = {9, 3, 3};
    matrix[5] = {5, 0, 5};
    matrix[6] = {5, 5, 0};
    matrix[7] = {1, 1, 1};

}

int Game_Matrix::get_index(std::vector<Move> &choices) {
    bool a[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        if (choices[i] == Move::D) {
            a[i] = 1;
        }
    }
    return a[0]*4 + a[1]*2 + a[2]*1;
}

void Game_Matrix::get_result(std::vector<Move>& choices) {
    int index = get_index(choices);
    results = matrix[index];
}
