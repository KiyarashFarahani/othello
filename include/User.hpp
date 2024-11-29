#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

class user {
protected:
    int id;
    string username;
    string password;
    int best_score;

public:
    user();
    user(int id, string username, string password);
    string getUsername() const;
    string getPassword() const;
    int getBestScore() const;
    void setBestScore(int score);
};

#endif
