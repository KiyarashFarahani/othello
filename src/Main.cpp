#include "../include/Game.hpp"
#include "../include/User.hpp"

int main() {

    Game game;

    while ( game.running() ) {

       game.update();

       game.render();

    }

    return 0;
}