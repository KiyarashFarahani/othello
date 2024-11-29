#include "../include/Start.hpp"

Start::Start() { this->initStart(); }
Start::~Start() {}

void Start::initStart() {
    
    if (!this->font.loadFromFile("../assets/fonts/SpaceMono-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    this->welcomeMessage = "Othello";
    this->messageIndex = 1;

    this->welcomeText.setFont(this->font);
    this->welcomeText.setCharacterSize(80);
    this->welcomeText.setFillColor(sf::Color::White);
    this->welcomeText.setPosition((float)this->window->getSize().x / 2, (float)this->window->getSize().y / 2);
    this->welcomeText.setOrigin(this->welcomeText.getLocalBounds().width / 2.0f, this->welcomeText.getLocalBounds().height / 2.0f);
}

void Start::update() {
    
    this->pollEvents();

    if (this->messageIndex <= this->welcomeMessage.length()) {

        this->welcomeText.setString(this->welcomeMessage.substr(0, this->messageIndex++));

        sf::FloatRect textBounds = this->welcomeText.getLocalBounds();
        this->welcomeText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                    textBounds.top + textBounds.height / 2.0f);
        this->welcomeText.setPosition((float)this->window->getSize().x / 2,
                                      (float)this->window->getSize().y / 2);
    }
}

void Start::render() {
    this->window->clear(sf::Color::Black);
    this->window->draw(this->welcomeText);
    this->window->display();
}
