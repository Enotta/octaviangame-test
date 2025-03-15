#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
	sf::RenderWindow window;
public:
	Game(sf::Texture texture, int height, int number);
	void run();
};