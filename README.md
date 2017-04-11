# 2d_game_engine
A 2d game engine made in C++

The purpose of this project was to learn more about software architecture, as well as to create the foundation of a future 2D game project.

# Graphics

This engine is using SDL2 to render sprites onto the screen.

# Level Loading

This engine adopts a data-driven design for game levels. Levels are created in a tile-based application, "Tiled" for example, and are exported as an XML file. The LevelParser class handles the parsing of these XML files, and creates a usable Level object with the parsed data. I used the tinyxml library to parse the XML files, as well as zlib to handle the compressed data in the XML files.

# Game States

A FSM (Finite-State Machine) is used to handle the game states. The current game states, with corresponding classes named after them are: MainMenuState, PlayState, PauseState, GameOverState. Game states are managed by the GameStateMachine class, which handles the GameState's using a stack implemented with an STL vector.

