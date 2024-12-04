#include "../include/User.hpp"

User::User() : id(0), username(""), password(""), best_score(0) {}
User::User(int id, string username, string password) : id(id), username(username), password(password), best_score(0) {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
int User::getBestScore() const { return best_score; }

void User::setBestScore(int score) { best_score = score; }

void User::ensureUserFileExists(const std::string& filePath) {
	if (!std::filesystem::exists(filePath)) {
		std::ofstream outFile(filePath);
		if (!outFile)
			std::cerr << "Error: Unable to create \"users.txt\"." << std::endl;
	}
}

User* User::login(const string& username, const string& password) {
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
            return new User(id, fileUsername, filePassword);
        }
    }

    file.close();
    return nullptr;
}

User* User::registerUser(const string& username, const string& password) {
	ensureUserFileExists("../users.txt");
    fstream file("../users.txt");
    if (!file) {
        cerr << "Unable to open the user file for reading." << endl;
        return nullptr;
    }

    string line;
    int id = 0;
    string fileUsername, filePassword;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        id = stoi(line.substr(0, pos1));
        fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);
        filePassword = line.substr(pos2 + 1, pos3 - pos2 - 1);

        if (fileUsername == username) {
            cerr << "Username already exists." << endl;
            return nullptr;
        }
    }

    int newId = id + 1;
    string newUserLine = to_string(newId) + "," + username + "," + password + ",0\n";

	ensureUserFileExists("../users.txt");
    ofstream outFile("../users.txt", ios::app);
    if (!outFile) {
        cerr << "Unable to open the user file for writing." << endl;
        return nullptr;
    } else {
        outFile << newUserLine;
        outFile.close();
        return new User(newId, username, password);
    }
}