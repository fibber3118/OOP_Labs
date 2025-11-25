#include "Game_Matrix.h"



Game_Matrix::Game_Matrix(const std::string filename) {
    results.resize(3);
    matrix.resize(8);
    for (int i = 0; i < 8; i++) {
        matrix[i].resize(3);
    }

    if (filename.empty()) {
        matrix[0] = {7, 7, 7}; // CCC
        matrix[1] = {3, 3, 9}; // CCD
        matrix[2] = {3, 9, 3}; // CDC
        matrix[3] = {0, 5, 5}; // CDD
        matrix[4] = {9, 3, 3}; // DCC
        matrix[5] = {5, 0, 5}; // DCD
        matrix[6] = {5, 5, 0}; // DDC
        matrix[7] = {1, 1, 1}; // DDD
    } else {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::invalid_argument("Не удалось открыть файл матрицы: " + filename);
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                if (!(file >> matrix[i][j])) {
                    throw std::runtime_error("Ошибка файла матрицы (ожидается 8 строк по 3 числа)");
                }
            }
        }
    }
}


int Game_Matrix::get_index(std::vector<Move> &choices) {
    bool a[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        if (choices[i] == Move::D) {
            a[i] = 1;
        }
    }
    return a[0] * 4 + a[1] * 2 + a[2] * 1;
}

void Game_Matrix::get_result(std::vector<Move> &choices) {
    int index = get_index(choices);
    results = matrix[index];
}
