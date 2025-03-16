#include "Game.h"
#include <stdexcept>
#include <iostream>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    try {
        sf::Texture symbolsTexture1;
        sf::Texture symbolsTexture2;
        sf::Texture symbolsTexture3;
        if (!symbolsTexture1.loadFromFile("assets/symbols1.png") ||
            !symbolsTexture2.loadFromFile("assets/symbols2.png") ||
            !symbolsTexture3.loadFromFile("assets/symbols3.png")) {
            throw std::runtime_error("Failed to load symbols texture!");
        }

        const int SYMBOL_HEIGHT = 100; 
        const int NUM_SYMBOLS = 5; 

        Game game(
            new sf::Texture[3] {symbolsTexture1, symbolsTexture2, symbolsTexture3},
            SYMBOL_HEIGHT,
            NUM_SYMBOLS
        );
        game.run();
    }
    catch (std::exception& e) {
        sf::err() << "Error: " << e.what() << std::endl;
    }
}