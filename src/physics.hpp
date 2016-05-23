#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>

/**
 * @file physics.hpp
 */

/**
 * Actual Game of Life
 * @param field Game board. True means that square is colored and false that it isn't.
 * @param map_size_x Horizontal size of game board.
 * @param map_size_y Vertical size of game board.
 * @returns Game board after simulation
 */
std::vector<std::vector<bool>> simulate(const std::vector<std::vector<bool>>& field,
                                        int map_size_x, int map_size_y);

#endif  // PHYSICS_HPP
