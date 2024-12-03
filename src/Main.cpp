#include "../include/Game.hpp"
#include "../include/User.hpp"
#include "../include/Admin.hpp"

int main() {

    // Test Login for Admin
    Admin admin(0, "admin", "admin");

    string testUsername, testPassword;

    // Admin login test
    cout << "Testing Admin Login:" << endl;
    cout << "Enter admin username: ";
    cin >> testUsername;
    cout << "Enter admin password: ";
    cin >> testPassword;

    Admin* loggedInAdmin = admin.login(testUsername, testPassword);
    if (loggedInAdmin) {
        cout << "Admin login successful!" << endl;

        // Test delete user
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

    // Game game;

    // while ( game.running() ) {

    //    game.update();

    //    game.render();

    // }

    return 0;
}