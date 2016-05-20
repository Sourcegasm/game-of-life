#ifndef GAME_HPP
#define GAME_HPP

#include "physics.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

/**
 * @file game.hpp
 */

class Game {
  private:
  	bool paused;
    const int map_size = 80;
    const unsigned int window_size = 800;
    double ups = 1000.0 / 60.0;

    sf::RenderWindow window;
    std::vector<std::vector<bool>> field;
    std::vector<std::vector<sf::RectangleShape>> squares;
    std::vector<char> v;
    void render();
    void handle_mouse_click();
    void update();
    void pause();
  public:
    Game();
    void run();
};

#endif  // GAME_HPP
