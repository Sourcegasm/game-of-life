#include "physics.hpp"

std::vector<std::vector<bool>> simulate(const std::vector<std::vector<bool>>& field, int map_size) {
    std::vector<std::vector<bool>> result;
    for (int i = 0; i < map_size; ++i) {
        std::vector<bool> line(map_size, false);
        result.push_back(line);
    }

    for (int y = 0; y < map_size; ++y) {
        for (int x = 0; x < map_size; ++x) {
            int x1 = x - 1;
            int y1 = y - 1;

            int x2 = x;
            int y2 = y - 1;

            int x3 = x + 1;
            int y3 = y - 1;

            int x4 = x - 1;
            int y4 = y;

            int x5 = x + 1;
            int y5 = y;

            int x6 = x - 1;
            int y6 = y + 1;

            int x7 = x;
            int y7 = y + 1;

            int x8 = x + 1;
            int y8 = y + 1;

            std::vector<int> xs = {x1, x2, x3, x4, x5, x6, x7, x8};
            std::vector<int> ys = {y1, y2, y3, y4, y5, y6, y7, y8};

            int live_neighbors = 0;

            for (int i = 0; i < 8; ++i) {
                if (xs[i] < 0 || xs[i] >= map_size || ys[i] < 0 || ys[i] >= map_size) {
                    continue;
                }

                if (field[ys[i]][xs[i]]) {
                    ++live_neighbors;
                }
            }

            bool is_alive = field[y][x];

            if (live_neighbors < 2 && is_alive) {
                result[y][x] = false;
            } else if (is_alive && (live_neighbors == 2 || live_neighbors == 3)) {
                result[y][x] = true;
            } else if (is_alive && live_neighbors > 3) {
                result[y][x] = false;
            } else if (!is_alive && live_neighbors == 3) {
                result[y][x] = true;
            }
        }
    }

    return result;
}
