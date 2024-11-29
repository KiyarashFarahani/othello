#ifndef Start_HPP
#define Start_HPP

#include "Game.hpp"
#include <string>

class Start : public Game {
private:

    sf::Font font;
    sf::Text welcomeText;
    std::string welcomeMessage;
    int messageIndex;

    void initStart();

public:

    Start();
    virtual ~Start();

    void update() override;
    void render() override;
};

#endif
