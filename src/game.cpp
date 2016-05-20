#include "game.hpp"
#include "physics.cpp"

Game::Game(){
    int square_size = window_size / map_size;
    paused = true;
    
    window.create(sf::VideoMode(window_size, window_size), "Game of life");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    int k = 0;
    for (int i = 0; i < map_size; ++i) {
        std::vector<bool> field_line(80, false);
        field.push_back(field_line);

        std::vector<sf::RectangleShape> line;

        for (int j = 0; j < map_size; ++j) {
            sf::RectangleShape sq(sf::Vector2f(square_size-1, square_size-1));
            sq.setPosition(i * square_size, j * square_size);
            line.push_back(sq);
            k++;
        }
        squares.push_back(line);
    }
}

void Game::run() {
    double timeDelta = 0;
    const double time = 1000.0 / 30.0;
    auto previousTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());


    while(window.isOpen()){
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        timeDelta += now.count() - previousTime.count();
        previousTime = now;

        while (timeDelta > time) {
            update();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }  else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        pause();
                    } else if(event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && paused) {
                    handle_mouse_click();
                }

            }

            timeDelta -= time;
        }

        render();
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    if (!paused) {
        field = simulate(field);
    }

    for (int y = 0; y < 80; ++y) {
        for (int x = 0; x < 80; ++x) {
            if (field[y][x]) {
                squares[y][x].setFillColor(sf::Color::Black);
            } else {
                squares[y][x].setFillColor(sf::Color::White);
            }
        }
    }
}

void Game::pause() {
    paused = !paused;
}

void Game::handle_mouse_click() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    std::cout << "Clicked " << mouse_pos.x << " " << mouse_pos.y << std::endl;
    int square_size = window_size / map_size;
    int y = mouse_pos.x / square_size;
    int x = mouse_pos.y / square_size;

    if (y >= 0 && y < 80 && x >= 0 && x < 80) {
        field[y][x] = !field[y][x];
    }
}

void Game::render() {
    window.clear(sf::Color(0, 0, 0, 255));

    for(int i = 0; i < map_size; ++i) {
        for(int j = 0; j < map_size; ++j) {
            window.draw(squares[i][j]);
        }
    }

    window.display();
}
