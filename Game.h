#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <thread>
#include "Drum.h"
#include "Button.h"

class Game {
private:
    sf::RenderWindow window;
    Drum drum1, drum2, drum3;
    Button startButton, stopButton;
    sf::Font font = sf::Font("assets/StalinistOne-Regular.ttf");
    int winAmount;
    enum class State { Idle, Spinning };
    State currentState;
    sf::Clock timer;
    sf::Clock expireTimer;

public:
	Game(sf::Texture* textures, int height, int number);
	void run();
	void update();
	void calculateWin();
	void render();
};