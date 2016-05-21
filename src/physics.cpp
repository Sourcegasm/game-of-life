#include "physics.hpp"

std::vector<std::vector<bool>> simulate(const std::vector<std::vector<bool>>& field, int map_size) {
    std::vector<std::vector<bool>> result;
    for (int i = 0; i < map_size; ++i) {
        std::vector<bool> line(map_size, false);
        result.push_back(line);
    }

    for (int y = 0; y < map_size; ++y) {
        for (int x = 0; x < map_size; ++x) {

            std::vector<int> xs, ys;
            for (int i = 0; i < 9; ++i) {
                if (i != 4) {
                    xs.push_back(x + i % 3 - 1);
                    ys.push_back(y + i / 3 - 1);
                }
            }

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
