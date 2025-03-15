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
    int winAmount;
    enum class State { Idle, Spinning, Win };
    State currentState;
    sf::Clock timer;

public:
	Game(sf::Texture texture, int height, int number);
	void run();
	void update();
	void calculateWin();
	void render();
};