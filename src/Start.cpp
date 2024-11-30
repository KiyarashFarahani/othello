#include "../include/Start.hpp"

// constructor
Start::Start() {
    this->initStart();
    this->messageComplete = false;
    this->fadeInProgress = false;
    this->fadeProgress = 0.0f; // To track fade progress (from 0 to 1)
}

// private
void Start::initStart() {
    if (!this->font.loadFromFile("../assets/fonts/SpaceMono-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    this->welcomeMessage = "Othello";
    this->messageIndex = 1;

    this->othelloText.setFont(this->font);
    this->othelloText.setCharacterSize(80);
    this->othelloText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = this->othelloText.getLocalBounds();
    this->othelloText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    this->othelloText.setPosition((float)this->window->getSize().x / 2, (float)this->window->getSize().y / 2 - 50);

    this->continueText.setFont(this->font);
    this->continueText.setCharacterSize(40);
    this->continueText.setFillColor(sf::Color::Black);  // Start with black color
    this->continueText.setString("Press Enter to continue");
    sf::FloatRect continueBounds = this->continueText.getLocalBounds();
    this->continueText.setOrigin(continueBounds.width / 2.0f, continueBounds.height / 2.0f);
    this->continueText.setPosition((float)this->window->getSize().x / 2, (float)this->window->getSize().y / 2 + 50);
}

// public
void Start::update() {
    this->pollEvents();

    // Handle the "Othello" message animation
    if (this->messageIndex <= this->welcomeMessage.length()) {
        this->othelloText.setString(this->welcomeMessage.substr(0, this->messageIndex++));

        sf::FloatRect textBounds = this->othelloText.getLocalBounds();
        this->othelloText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        this->othelloText.setPosition((float)this->window->getSize().x / 2, (float)this->window->getSize().y / 2 - 50);

        sf::sleep(sf::seconds(0.25));
    }
    else if (!this->messageComplete) {
        // Once "Othello" is fully displayed, start the fade-in of "Press Enter to continue"
        this->messageComplete = true;
        this->fadeInProgress = true; // Start the fade animation
    }

    // Fade-in effect for "Press Enter to continue"
    if (this->fadeInProgress && this->fadeProgress < 1.0f) {
        this->fadeProgress += 0.01f; // Increment fade progress (you can adjust the speed here)
        if (this->fadeProgress > 1.0f) {
            this->fadeProgress = 1.0f; // Ensure it doesn't exceed 1
        }

        // Update the color of the text (interpolating from black to white)
        int red = static_cast<int>(255 * this->fadeProgress);
        int green = static_cast<int>(255 * this->fadeProgress);
        int blue = static_cast<int>(255 * this->fadeProgress);
        this->continueText.setFillColor(sf::Color(red, green, blue));
    }
}

void Start::render() {
    this->window->clear(sf::Color::Black);
    this->window->draw(this->othelloText);

    // Only draw the continueText if the message is complete and fade-in is in progress
    if (this->messageComplete) {
        this->window->draw(this->continueText);
    }

    this->window->display();
}
