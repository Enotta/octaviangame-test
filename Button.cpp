#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string label) : text(font, label), isHovered(false) {
	shape.setPosition(pos);
	shape.setSize(size);

	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(pos.x + 10, pos.y + 10));
}

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (shape.getGlobalBounds().contains(mousePos)) {
		isHovered = true;
		if (event.is<sf::Event::MouseButtonReleased>() && 
			event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {
			if (onClick) onClick();
		}
	}
	else {
		isHovered = false;
	}
}

void Button::draw(sf::RenderWindow& window) {
	shape.setFillColor(isHovered ? sf::Color(200, 200, 200) : sf::Color::White);
	window.draw(shape);
	window.draw(text);
}

void Button::setOnClick(std::function<void()> callback) {
	onClick = callback;
}