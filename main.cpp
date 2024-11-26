#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class user {

    protected:

        int id;
        string username;
        string password;
        int best_score;

    public:

        user () {}
        user ( int id, string username, string password ) : id(id), username(username), password(password), best_score(0) {}

        string getUsername () const { return username; }
        string getPassword () const { return password; }
        int getBestScore () const { return best_score; }

        void setBestScore ( int score ) { best_score = score; }

        // a function for login
        // a function for sign up
};

class admin : public user {

    public:

        //a function for delete user
};

int main(){

    return 0;
}