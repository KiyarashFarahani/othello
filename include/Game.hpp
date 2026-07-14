#ifndef GAME_HPP
#define GAME_HPP

#include "char_traits_fix.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unistd.h>

class Game {

    protected:

        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        sf::Font font;
        sf::Text leftText;
        sf::Text rightText;

        static const int BOARD_SIZE = 8;
        int board[BOARD_SIZE][BOARD_SIZE];

        void initVariables();
        void initWindow();
        void initBoard();

    public:

        Game();
        virtual ~Game();

        const bool running() const;
        virtual void pollEvents();
        virtual void update();
        virtual void render();
        sf::VertexArray drawGrid(float topOffset);
};

#endif