#include "../include/User.hpp"

user::user() : id(0), username(""), password(""), best_score(0) {}

user::user(int id, string username, string password) : id(id), username(username), password(password), best_score(0) {}

string user::getUsername() const { return username; }

string user::getPassword() const { return password; }

int user::getBestScore() const { return best_score; }

void user::setBestScore(int score) { best_score = score; }
