#include "game.hpp"

Game::Game(){
    paused = true;

    unsigned int window_size_x = square_size * map_size_x;
    unsigned int window_size_y = square_size * map_size_y;

    window.create(sf::VideoMode(window_size_x, window_size_y), "Game of life");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    int k = 0;
    for (int i = 0; i < map_size_y; ++i) {
        std::vector<bool> field_line(map_size_x, false);
        field.push_back(field_line);

        std::vector<sf::RectangleShape> line;
        for (int j = 0; j < map_size_x; ++j) {
            sf::RectangleShape sq(sf::Vector2f(square_size-1, square_size-1));
            sq.setPosition(j * square_size, i * square_size);
            line.push_back(sq);
            k++;
        }
        squares.push_back(line);
    }
}

void Game::run() {
    double time_delta = 0;
    auto previous_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch());

    while(window.isOpen()){
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch());
        time_delta += now.count() - previous_time.count();
        previous_time = now;

        while (time_delta > ups) {
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
                }

            }

            time_delta -= ups;
        }

        render();
    }
}

void Game::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && paused) {
        handle_mouse_click(true);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && paused) {
        handle_mouse_click(false);
    }

    if (!paused) {
        field = simulate(field, map_size_x, map_size_y);
    }

    for (int y = 0; y < map_size_y; ++y) {
        for (int x = 0; x < map_size_x; ++x) {
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
    if (paused) {
        ups = 1000.0 / 60.0;
    } else {
        ups = 1000.0 / 5.0;
    }
}

void Game::handle_mouse_click(bool color) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int x = mouse_pos.x / square_size;
    int y = mouse_pos.y / square_size;

    if (y >= 0 && y < map_size_y && x >= 0 && x < map_size_x) {
        field[y][x] = color;
    }
}

void Game::render() {
    window.clear(sf::Color(0, 0, 0, 255));

    for(int i = 0; i < map_size_y; ++i) {
        for(int j = 0; j < map_size_x; ++j) {
            window.draw(squares[i][j]);
        }
    }

    window.display();
}
