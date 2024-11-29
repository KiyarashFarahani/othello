#include "../include/Menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

void menuWindow() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Othello", sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/SpaceMono-Bold.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    string str = "Welcome!";
    int i = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        sf::Text welcomeText;
        welcomeText.setFont(font);
        welcomeText.setString(str.substr(0, i++));
        sf::sleep(sf::seconds(0.25));
        welcomeText.setCharacterSize(48);
        welcomeText.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = welcomeText.getLocalBounds();
        welcomeText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        welcomeText.setPosition((float)window.getSize().x / 2, (float)window.getSize().y / 2);

        window.clear();
        window.draw(welcomeText);
        window.display();
    }
}
