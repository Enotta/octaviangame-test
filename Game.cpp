#include "Game.h"

Game::Game(sf::Texture texture, int height, int number) {
    this->window = sf::RenderWindow(sf::VideoMode({ 800, 600 }), "Slot Machine");
}
    
void Game::run() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}