#ifndef START_HPP
#define START_HPP

#include "Game.hpp"
#include <string>

class Start : public Game {

    private:

        sf::Font font;
        sf::Text othelloText;
        sf::Text continueText;
        std::string welcomeMessage;
        int messageIndex;
        bool messageComplete;
        bool fadeInProgress;
        float fadeProgress;

        void initStart();

    public:

        Start();

        void update() override;
        void render() override;
};

#endif
