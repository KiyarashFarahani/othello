#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class User {
protected:
    int id;
    string username;
    string password;
    int best_score;
public:
    User();
    User(int id, string username, string password);
    virtual ~User();
    string getUsername() const;
    string getPassword() const;
    int getBestScore() const;
    void setBestScore(int score);
    static User* login(const string& username, const string& password);
    static User* registerUser(const string& username, const string& password);
};

#endif
