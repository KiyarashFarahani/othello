#include "../include/Menu.hpp"
#include "../include/User.hpp"

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

void Menu::clearScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

// Register a new user
void Menu::registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* newUser = User::registerUser(username, password);
	clearScreen();
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
	clearScreen();
    if (username == "admin") {
        Admin admin(0, "admin", "admin");
        Admin* loggedInAdmin = admin.login(username, password);
        if (loggedInAdmin) {
            cout << "Admin login successful!" << endl;
            cout << "\nTesting User Deletion:" << endl;
            cout << "Enter username to delete: ";
            string deleteUsername;
            cin >> deleteUsername;
			clearScreen();
            if (!loggedInAdmin->deleteUser(deleteUsername))
                cout << "Failed to delete user: " << deleteUsername << endl;

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
struct userScore {
    int score;
    string name;
};
void Menu::showBestScores() {
    User::ensureUserFileExists("../users.txt");
	fstream file("../users.txt");
    if (!file) {
        cerr << "Unable to open the user file for reading.";
        return ;
    }

    vector<userScore> us;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find('\n', pos3 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
            cerr << "Malformed line: " << line << endl;
            continue;
        }

        userScore temp;
        temp.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        temp.score = stoi(line.substr(pos3 + 1, pos4 - pos3 -1));
        us.push_back(temp);
    }

    bool condition = true;
    while (condition){
        condition = false;
        for ( int i = 0; i < us.size()-1; i++ ){
            if ( us[i].score < us[i+1].score ){
                userScore temp;
                temp = us[i];
                us[i] = us[i+1];
                us[i+1] = temp;
                condition = true;
            }
        }
    }

    for ( int i=0 ; i<us.size() ; i++ ){
        cout << i+1 << ") " << us[i].name << " with Score: " << us[i].score << endl;
    }
    
    file.close();
    return;
}

// Start the game
void Menu::playGame(User* user) {
	clearScreen();
	Game game;
	while (game.running()) {
		game.update();
		game.render();
	}
}

// Start the menu and main control loop
void Menu::startMenu() {
    char choice;
    clearScreen();
    while (true) {
        displayMainMenu();
        cin >> choice;
        clearScreen();

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
			clearScreen();
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        default:
			clearScreen();
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}