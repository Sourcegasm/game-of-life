#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

/**
 * @file game.hpp
 */

class Game {
  private:
  	bool paused;
    int map_size = 80, window_size = 800;
    sf::RenderWindow window;
    std::vector<std::vector<sf::RectangleShape>> squares;
    std::vector<std::pair<int, int>> colored, last_colored;
    std::vector<char> v;
    void color_squares();
    void handle_mouse_click();
    void first_update();
    void update();
    void pause();
  public:
    Game();
    void run();
};

#endif  // GAME_HPP