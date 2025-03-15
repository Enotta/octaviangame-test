#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
	sf::RectangleShape shape;
	sf::Text text;
	std::function<void()> onClick;
	bool isHovered;
public:
	Button(sf::Vector2f& pos, sf::Vector2f& size, std::string& label);
	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void setOnClick(std::function<void()> callback);
};