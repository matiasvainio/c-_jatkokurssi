#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

const auto COLS = 150, ROWS = 150;

double map[ROWS][COLS] = {0};

double influence_map[ROWS][COLS];

inline double distance(int c0, int r0, int c1, int r1) {
    return sqrt((r0 - r1) * (r0 - r1) + (c0 - c1) * (c0 - c1));
}

int main(int, char **) {
    std::vector<int> indices;

    map[1][5] = 2;
    map[1][10] = 3;
    map[2][1] = 4;
    map[2][9] = 2;
    map[4][3] = 2;
    map[4][5] = 1;
    map[5][6] = 1;

    map[13][2] = -2;
    map[11][10] = -2;
    map[3][15] = -2;
    map[5][12] = -4;
    map[8][14] = -2;

    for (size_t i = 0; i < ROWS; i++) {
        indices.push_back(i);
    }

    auto start = std::chrono::steady_clock::now();

    auto calculate_influence = [](const int &n) {
        for (size_t r0 = 0; r0 < COLS; r0++) {
            for (size_t c0 = 0; c0 < COLS; c0++) {
                influence_map[r0][c0] = 0;

                for (size_t r1 = 0; r1 < ROWS; r1++) {
                    for (size_t c1 = 0; c1 < COLS; c1++) {
                        double i0 = map[r1][c1];
                        double d = distance(c0, r0, c1, r1);
                        influence_map[r0][c0] = influence_map[r0][c0] + (i0 / (1 + d));
                    }
                }
            }
        }
    };

    std::for_each(indices.cbegin(), indices.cend(), calculate_influence);

    auto end = std::chrono::steady_clock::now();

    // for (size_t i = 0; i < ROWS; i++) {
    //     for (size_t j = 0; j < COLS; j++) {
    //         if (influence_map[i][j] >= 0) {
    //             std::cout << "W ";
    //         } else {
    //             std::cout << "B ";
    //         }
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " sec";
}
