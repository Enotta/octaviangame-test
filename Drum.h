#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <iostream>

class Drum {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int symbolHeight;
    int numSymbols;
    int windowPosition;
    float currentOffset;
    float targetOffset;
    float spinSpeed;
    bool isSpinning;
    bool isStopping;

public:
    Drum(sf::Texture& tex, int height, int number, int windowPos);
    void startSpinning(int seed);
    void stop(int seed);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isStopped();
    int getCurrentSymbol();
};