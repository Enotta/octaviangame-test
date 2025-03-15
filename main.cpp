#include "Game.h"
#include <stdexcept>
#include <iostream>

int main()
{
    try {
        sf::Texture symbolsTexture;
        if (!symbolsTexture.loadFromFile("assets/symbols.png")) {
            throw std::runtime_error("Failed to load symbols texture!");
        }

        const int SYMBOL_HEIGHT = 100; 
        const int NUM_SYMBOLS = 5; 

        Game game(
            symbolsTexture,
            SYMBOL_HEIGHT,
            NUM_SYMBOLS
        );
        game.run();
    }
    catch (std::exception& e) {
        sf::err() << "Error: " << e.what() << std::endl;
    }
}