#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
using namespace std;

void menuWindow();

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

	menuWindow();
    return 0;
}

void menuWindow(){
	// Create a window
	sf::RenderWindow window(sf::VideoMode(1600, 1200), "Othello");
	window.setFramerateLimit(60);

	string currentPath = filesystem::path(__FILE__).parent_path().string();
	sf::Font font;
	if(!font.loadFromFile(currentPath + "/SpaceMono-Bold.ttf"))
		window.close();
	std::string str = "Welcome!";
	int i = 1;


	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Text welcomeText;
		welcomeText.setFont(font);
		welcomeText.setString(str.substr(0, i++));
		sleep(sf::seconds(0.25));
		welcomeText.setCharacterSize(48);

		welcomeText.setFillColor(sf::Color::White);

		// Center the text
		sf::FloatRect textBounds = welcomeText.getLocalBounds();
		welcomeText.setOrigin(textBounds.left + textBounds.width / 2.0f,
					   textBounds.top + textBounds.height / 2.0f);
		welcomeText.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);

		window.clear();

		window.draw(welcomeText);
		
		window.display();
	}
	
}