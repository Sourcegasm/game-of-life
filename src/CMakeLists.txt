set(SOURCE_FILES
        main.cpp
        game.cpp
        physics.cpp
)

add_executable(Game_of_Life ${SOURCE_FILES})
target_link_libraries(Game_of_Life
        sfml-graphics
        sfml-window
        sfml-system
)
