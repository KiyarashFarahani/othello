#include "../include/Game.hpp"

Game::Game () { this->initVariables(); this->initWindow(); }
Game::~Game () { delete this->window; }

void Game::initVariables () { this->window = nullptr; }

void Game::initWindow () {

    sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow (
			this->videoMode,
			"Othello",
			sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar
	);
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

void Game::render () {

    this->window->clear(sf::Color(0,0,0,255));
    //draw game objects in here
    this->window->display();
}