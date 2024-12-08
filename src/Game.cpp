#include "../include/Game.hpp"

Game::Game () { this->initVariables(); this->initWindow(); }
Game::~Game () { delete this->window; }

void Game::initVariables () {
    this->window = nullptr;

	// set the working directory to project root and load font
	chdir("../");
    if (!this->font.loadFromFile("assets/fonts/SpaceMono-Bold.ttf")) {
        std::cout << "Error loading font\n";
        return;
    }
    
    // Initialize text objects
    this->leftText.setFont(this->font);
    this->rightText.setFont(this->font);
    
    this->leftText.setString("Player 1: ");
    this->rightText.setString("Player 2: ");

    this->leftText.setCharacterSize(24);
    this->rightText.setCharacterSize(24);
    
    this->leftText.setFillColor(sf::Color::White);
    this->rightText.setFillColor(sf::Color::White);
}

void Game::initWindow() {
    // Get the desktop resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Calculate the aspect ratio
    float aspectRatio = static_cast<float>(desktopMode.width) / desktopMode.height;

    // Check if the aspect ratio is approximately 16:9
    if (std::abs(aspectRatio - 16.0f / 9.0f) < 0.01f) {
        // If 16:9, use fullscreen mode
        this->videoMode = desktopMode;
        this->window = new sf::RenderWindow(
            this->videoMode,
            "Othello",
            sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar
        );
    } else {
        // Otherwise, use 1280x720 resolution without fullscreen
        this->videoMode = sf::VideoMode(1280, 720);
        this->window = new sf::RenderWindow(
            this->videoMode,
            "Othello",
            sf::Style::Close | sf::Style::Titlebar
        );
    }

    // Set the framerate limit
    this->window->setFramerateLimit(60);
}

// public functions

const bool Game::running () const { return this->window->isOpen(); }

void Game::pollEvents () {

    while ( this->window->pollEvent(this->ev) ) {

        switch ( this->ev.type ) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                    if ( this->ev.key.code == sf::Keyboard::Escape ) this->window->close();
                    break;

            default:
                break;
        }
    }
}

void Game::update () { this->pollEvents(); }

void Game::render() {
    // Clear the window with the board's background color
    this->window->clear(sf::Color(212, 172, 13, 255));

    // Get the window size and calculate grid dimensions
    sf::Vector2u windowSize = this->window->getSize();
    const int gridSize = 8;
    const int cellSize = 50;
    const float infoHeight = 70.0f;
    
    // Adjust the available height for the grid
    float availableHeight = windowSize.y - infoHeight;
    float scale = std::min(static_cast<float>(windowSize.x) / (gridSize * cellSize),
                          static_cast<float>(availableHeight) / (gridSize * cellSize));

    float boardWidth = gridSize * cellSize * scale;
    float offsetX = (windowSize.x - boardWidth) / 2;

    // Create black rectangles for the sides
    sf::RectangleShape leftRect(sf::Vector2f(offsetX, windowSize.y));
    leftRect.setFillColor(sf::Color::Black);

    sf::RectangleShape rightRect(sf::Vector2f(offsetX, windowSize.y));
    rightRect.setPosition(offsetX + boardWidth, 0);
    rightRect.setFillColor(sf::Color::Black);

    // Create info rectangle at the top
    sf::RectangleShape infoRect(sf::Vector2f(boardWidth, 75));
    infoRect.setPosition(offsetX, 0);
    infoRect.setFillColor(sf::Color(0, 0, 0));

    // Position the text
    leftText.setPosition(offsetX + 10, 20);
    rightText.setPosition(offsetX + boardWidth - rightText.getLocalBounds().width - 10, 20);

    // Draw everything
    this->window->draw(leftRect);
    this->window->draw(rightRect);
    this->window->draw(infoRect);
    
    // Draw the grid
    sf::VertexArray lines = drawGrid(infoHeight);  // Pass the infoHeight to drawGrid
    this->window->draw(lines);

    // Draw the text
    this->window->draw(leftText);
    this->window->draw(rightText);

    // Display the frame
    this->window->display();
}

sf::VertexArray Game::drawGrid(float topOffset) {
    const int gridSize = 8;
    const int cellSize = 50;

    sf::Vector2u windowSize = this->window->getSize();

    // adjust grid size, accounting for top offset
    float availableHeight = windowSize.y - topOffset;
    float scale = std::min(static_cast<float>(windowSize.x) / (gridSize * cellSize),
                          static_cast<float>(availableHeight) / (gridSize * cellSize));

    float offsetX = (windowSize.x - (gridSize * cellSize * scale)) / 2;
    float offsetY = topOffset + (availableHeight - (gridSize * cellSize * scale)) / 2;

    // grid lines
    sf::VertexArray lines(sf::Lines, 2*2*(gridSize+1));

    // vertical
    for (int i = 0; i <= gridSize; ++i) {
        float x = offsetX + i * cellSize * scale;
        lines.append(sf::Vertex(sf::Vector2f(x, offsetY), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(x, offsetY + gridSize * cellSize * scale), sf::Color::Black));
    }

    // horizontal
    for (int i = 0; i <= gridSize; ++i) {
        float y = offsetY + i * cellSize * scale;
        lines.append(sf::Vertex(sf::Vector2f(offsetX, y), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(offsetX + gridSize * cellSize * scale, y), sf::Color::Black));
    }

    return lines;
}
