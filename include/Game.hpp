#ifndef USER_HPP
#define USER_HPP

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#include <SFML/Network.hpp>

class Game {

    private:

        //variables
        //window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        void initVariables();
        void initWindow();

    public:

        Game();
        virtual ~Game();

        void pollEvents();
        const bool running() const;
        void update();
        void render();
};

#endif