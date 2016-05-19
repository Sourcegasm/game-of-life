#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game {
  private:
    sf::RenderWindow window;
    std::vector<std::vector<sf::Sprite>> squares;
    void update();
    void handle_mouse_click();
    void pause();
  public:
    Game();
    void run();
};

#endif  // GAME_HPP