#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>

/**
 * @file physics.hpp
 */

std::vector<std::vector<bool>> simulate(const std::vector<std::vector<bool>>& field,
                                                    int map_size_x, int map_size_y);

#endif  // PHYSICS_HPP
