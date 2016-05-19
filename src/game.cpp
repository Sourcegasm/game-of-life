#include "game.hpp"

Game::Game(){
    window.create(sf::VideoMode(800, 600), "Game of life");
    window.setFramerateLimit(30);
}

void Game::run(){
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Space) pause();
                    else if(!(event.key.code == sf::Keyboard::Escape)) break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) handle_mouse_click();
                default: break;
            }
        }
        update();
    }
}

void Game::update() {
    window.clear(sf::Color(240, 240, 240));

    for(auto line : squares) {
        for(sf::Sprite& sprite : line) {
            window.draw(sprite);
        }
    }
    window.display();
}

void Game::pause() {}

void Game::handle_mouse_click(){
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    // ...
    // check 
}
