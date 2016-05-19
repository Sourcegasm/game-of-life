#include "game.hpp"
#include "physics.cpp"

Game::Game(){
    int square_size = window_size / map_size;
    paused = true;
    
    window.create(sf::VideoMode(window_size, window_size), "Game of life");
    window.setFramerateLimit(30);
    int k = 0;
    for (int i = 0; i < map_size; ++i) {
        std::vector<sf::RectangleShape> line;
        for (int j = 0; j < map_size; ++j) {
            sf::RectangleShape sq(sf::Vector2f(square_size-1, square_size-1));
            sq.setPosition(i * square_size, j * square_size);
            line.push_back(sq);
            k++;
        }
        squares.push_back(line);
    }
    std::vector<std::pair<int, int>> colored, last_colored;
    colored.push_back(std::pair<int, int>(10, 10));

    first_update();
}

void Game::run(){
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Space) {
                        pause();
                        break;
                    } else if(!(event.key.code == sf::Keyboard::Escape)){
                        break;
                    }
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) handle_mouse_click();
                default: break;
            }
        }
        color_squares();
        update();
    }
}

void Game::first_update() {
    window.clear(sf::Color(100, 100, 100));
    int k = 0;
    for(int i = 0; i < map_size; ++i) {
        for(int j = 0; j < map_size; ++j) {
            window.draw(squares[i][j]); k++;
        }
    }
}

void Game::update() {
    for(auto p : last_colored) {
        window.draw(squares[p.first][p.second]);
    }
    for(auto p : colored) {
        window.draw(squares[p.first][p.second]);
    }
    window.display();
}

void Game::pause() {
    paused = ! paused;
}

void Game::handle_mouse_click() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    std::cout << "Clicked " << mouse_pos.x << " " << mouse_pos.y << std::endl;
    int square_size = window_size / map_size;
    colored.push_back(std::pair<int, int>(mouse_pos.x / square_size, mouse_pos.y / square_size));
}

void Game::color_squares() {
    if (!paused) {
        std::cout << "Update" << std::endl;
        auto last_colored(colored);
        colored = simulate(colored);
        for(auto p : last_colored) {
            squares[p.first][p.second].setFillColor(sf::Color::White);
        }
    }
    for(auto p : colored) {
        squares[p.first][p.second].setFillColor(sf::Color::Black);
    }
}