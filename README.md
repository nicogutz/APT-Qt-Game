# [APT Game Full Documentation](https://nicogutz.github.io/)
### [nicogutz.github.io](https://nicogutz.github.io/)
<br>

# APT Game Project


## Project Summary

APT is a dynamic, interactive game developed using C++ and the Qt framework. The game combines strategic movement, attack mechanisms, and various behavior models to create a unique gaming experience.

## Contributors

    • Nicolas Gutrierrez: Implemented the model and the behaviors (GameObject, GameObjectModel, GamePixmapItem, publicEnums, GameObjectSettings, + all the behaviors)

    • Nur Alda: Implemented the views and the renderers (GameView, Renderer, TextRenderer, ColorRenderer, SpriteRenderer)

    • Salma Loukili: Implemented the controller and the UI (ModelFactory, GameController, GameWindow, GameWindow.ui, Node.h)
    

## Main Classes

GameWindow, GameController, GameView, GameObject, GameObjectModel + Renderers & Behaviors

## Game Features Overview

    • Three different visualizations (Color, Text and Sprites)

    • Seemless switch between visualizations during any point of the game

    • Moving protagonist in a large world grid with Tiles of different values

    • Take Health packs to gain health

    • Enemies, Poison Enemies and Moving Enemies
    
    • Enemies attack back, custom death animations per view

    • Attack Enemies to gain Energy (but costs health)

    • Doorways leading to next/previous levels

    • Poisoned tiles after killing poison enemy

    • Random poisoning of the world by PEnemy

    • Variable world size, chosen by the user at the beginning of the game

    • Automatic router to any position in world

    • Infinite automatic router 
    
    • Automatic healthpack grabbing and enemy attacking on low Health/Energy 

    • Path Visualization of the autorouter

    • Procedurally generated levels with increasing difficulty

    • Game over if out of health or energy

    • Pause / Resume / Restart / Quit game

    • Zoom in/out the world grid

    • Timer display

    • User text input commands when in Text view

    • Animations for: Protagonist moving, attacking enemies, stepping on poisoned tile and Enemy being attacked, dying and moving

    • Health and energy of protagonist displayed

    • Level, number of enemies and number of health packs displayed
    

## Weekly Progress Log

    • Week 6-11: Architecture of the game and UML
    • Week 10-12: Basic implementations and experimenting with QT
    • Week 13: Basic world grid and window implemented + model and basic behaviors implemented
    • Christmas Holiday: 
        - Day 1-3: Basic Integration of the world library with the model and the visualizations
        - Day 4-6: Finalized behaviors and integration to the window, integration of pathfinder, basic enemies
        - Day 6-8: Implementation of doorways and levels, integration of moving and poison enemies, finalized controller and wnidow, improved UI 
        - Day 8-10: Implementation of animations, improving the views, UML, Readme, Refactoring and documenting code



