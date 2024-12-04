#include "../include/Admin.hpp"
//#include "User.cpp"

Admin::Admin() : User(0, "", "") {}
Admin::Admin(int id, string username, string password) : User(id, username, password) {}

Admin* Admin::login(const string& username, const string& password){
	ensureUserFileExists("../users.txt");
    fstream file("../users.txt");
    if (!file) {
        cerr << "Unable to open the user file for reading.";
        return nullptr;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
            cerr << "Malformed line: " << line << endl;
            continue;
        }

        int id = stoi(line.substr(0, pos1));
        string fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string filePassword = line.substr(pos2 + 1, pos3 - pos2 - 1);

        if (fileUsername == username && filePassword == password) {
            file.close();
            return new Admin(id, fileUsername, filePassword);
        }
    }

    file.close();
    return nullptr;
}

bool Admin::deleteUser(const string& username) {

    if(username=="admin") return false;

	ensureUserFileExists("../users.txt");
	ifstream inputFile("../users.txt");
    if (!inputFile) {
        cerr << "Unable to open the user file for reading." << endl;
        return false;
    }

    ofstream tempFile("../temp_users.txt");
    if (!tempFile) {
        cerr << "Unable to create a temporary user file." << endl;
        inputFile.close();
        return false;
    }

    string line;
    bool userFound = false;

    while (getline(inputFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) {
            cerr << "Malformed line: " << line << endl;
            continue;
        }

        string fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);

        if (fileUsername == username) {
            userFound = true; // Skip writing this user to the temp file
        } else {
            tempFile << line << endl; // Write valid lines to the temp file
        }
    }

    inputFile.close();
    tempFile.close();

    if (!userFound) {
        cerr << "User not found: " << username << endl;
        remove("../temp_users.txt"); // Remove the temp file if no changes were made
        return false;
    }

    // Replace the old file with the new one
    if (remove("../users.txt") != 0 || rename("../temp_users.txt", "../users.txt") != 0) {
        cerr << "Error updating the user file." << endl;
        return false;
    }

    cout << "User " << username << " deleted successfully." << endl;
    return true;
}