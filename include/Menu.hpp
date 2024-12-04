#ifndef MENU_HPP
#define MENU_HPP

#include "User.hpp"
#include "Admin.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Menu {
private:
    static void displayMainMenu();  // Display the main menu
    static void registerUser();     // Register a new user
    static User* loginUser();       // Log in an existing user
    static void showLastGame();     // Show the last game played
    static void showBestScores();   // Show the best scores
    static void playGame(User* user);  // Start the game

public:
    static void startMenu();   // Start the menu and main control loop
};

#endif // MENU_HPP