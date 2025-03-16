#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

class Button {
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	std::function<void()> onClick;
	bool isHovered;

public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string label, sf::Font* font);
	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void setOnClick(std::function<void()> callback);
};