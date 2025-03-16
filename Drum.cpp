#include "Drum.h"

Drum::Drum(sf::Texture& tex, int height, int number, int windowPos, Symbol order[5])
    : texture(tex), sprite(sf::Sprite(texture)), symbolHeight(height), numSymbols(number) {
    for (int i = 0; i < 5; i++) { this->order[i] = order[i]; }
    texture.setRepeated(true);
    currentOffset = 0;
    targetOffset = 0;
    windowPosition = windowPos;
    spinSpeed = 400;
    isSpinning = false;
    isStopping = false;
}

void Drum::startSpinning(int seed) {
    seed %= 5;
    spinSpeed = 300 + seed * 50;
    isSpinning = true;
    isStopping = false;
}

void Drum::stop(int seed) {
    if (isStopping) return;

    int targetSymbol = seed % (numSymbols * 3) + numSymbols;
    targetOffset = targetSymbol * symbolHeight;

    isSpinning = false;
    isStopping = true;
}

void Drum::update(float deltaTime) {
    if (isSpinning) {
        currentOffset += spinSpeed * deltaTime;
        currentOffset = fmod(currentOffset, numSymbols * symbolHeight);
    }
    else if (isStopping) {
        currentOffset += spinSpeed * deltaTime;

        if (currentOffset >= targetOffset) {
            currentOffset = targetOffset;
            isStopping = false;
        }
    }
}

void Drum::draw(sf::RenderWindow& window) {
    sf::IntRect rect(sf::Vector2(0, static_cast<int>(currentOffset)), sf::Vector2(static_cast<int>(texture.getSize().x), 3 * symbolHeight));
    sprite.setTextureRect(rect);
    sprite.setScale(sf::Vector2f(1.5, 1.5));
    sprite.setPosition(sf::Vector2f(windowPosition * sprite.getScale().x, 75));
    window.draw(sprite);
}

bool Drum::isStopped() {
    return !isSpinning && !isStopping;
}

Drum::Symbol Drum::getCurrentSymbol() {
    return order[static_cast<int>((currentOffset + symbolHeight) / symbolHeight) % numSymbols];
}