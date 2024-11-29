//#include "./include/Menu.hpp"
#include "./include/Game.hpp"
#include "./include/Start.hpp"

int main() {

    Start game;

    while ( game.running() ) {

       game.update();

       game.render();
        
    }

    return 0;
}