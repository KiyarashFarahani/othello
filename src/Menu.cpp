#include "../include/Menu.hpp"

using namespace std;

// Display the main menu
void Menu::displayMainMenu() {
    cout << "************** Main Menu **************" << endl;
    cout << "1. Register User" << endl;
    cout << "2. Play Game" << endl;
    cout << "3. Show Last Game" << endl;
    cout << "4. Show Best Scores" << endl;
    cout << "5. Exit" << endl;
    cout << "***************************************" << endl;
    cout << "Choose an option (1-5): ";
}

// Register a new user
void Menu::registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* newUser = User::registerUser(username, password);
    if (newUser) {
        cout << "Registration successful!" << endl;
    } else {
        cout << "Registration failed! Username may already exist." << endl;
    }
}

// Log in an existing user
User* Menu::loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "admin") {
        Admin admin(0, "admin", "admin");
        Admin* loggedInAdmin = admin.login(username, password);
        if (loggedInAdmin) {
            cout << "Admin login successful!" << endl;
            cout << "\nTesting User Deletion:" << endl;
            cout << "Enter username to delete: ";
            string deleteUsername;
            cin >> deleteUsername;

            if (loggedInAdmin->deleteUser(deleteUsername)) {
                cout << "User " << deleteUsername << " successfully deleted!" << endl;
            } else {
                cout << "Failed to delete user: " << deleteUsername << endl;
            }

            delete loggedInAdmin; // Clean up
        } else {
            cout << "Admin login failed. Check your credentials." << endl;
        }
    } else {
        User* loggedInUser = new User();
        loggedInUser = loggedInUser->login(username, password);
        if (loggedInUser) {
            cout << "Login successful!" << endl;
            return loggedInUser;
        } else {
            cout << "Login failed! Please check your username and password." << endl;
            return nullptr;
        }
    }
    
    // Ensure that we return a valid User pointer
    return nullptr;  // In case the function execution reaches here, return nullptr
}

// Show the last game played
void Menu::showLastGame() {}

// Show the best scores
void Menu::showBestScores() {}

// Start the game
void Menu::playGame(User* user) {}

// Start the menu and main control loop
void Menu::startMenu() {
    char choice;
    while (true) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case '1':
            registerUser();
            break;
        case '2': {
            User* user = loginUser();
            if (user) {
                playGame(user);
                delete user;
            }
            break;
        }
        case '3':
            showLastGame();
            break;
        case '4':
            showBestScores();
            break;
        case '5':
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}