#include "Game.h"

Game::Game(sf::Texture texture, int height, int number)
    : window(sf::VideoMode({ 1000, 600 }), "Slot Machine"),
    drum1(texture, height, number, 50),
    drum2(texture, height, number, 50 + height),
    drum3(texture, height, number, 50 + height * 2),
    startButton(sf::Vector2f(700, 325), sf::Vector2f(200, 50), static_cast<std::string>("Start")),
    stopButton(sf::Vector2f(700, 225), sf::Vector2f(200, 50), static_cast<std::string>("Stop")),
    currentState(State::Idle) {
    startButton.setOnClick([this]() {
        if (currentState == State::Idle || currentState == State::Win) {
            currentState = State::Spinning;
            srand(time(NULL));
            drum1.startSpinning(rand());
            drum2.startSpinning(rand());
            drum3.startSpinning(rand());
            timer.restart();
        }
    });

    stopButton.setOnClick([this]() {
        if (currentState == State::Spinning) {
            srand(time(NULL));
            drum1.stop(rand());
            drum2.stop(rand());
            drum3.stop(rand());
        }
    });
}

void Game::run() {
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event.has_value()) {
                sf::Event temp = event.value(); 
                if (temp.is<sf::Event::Closed>())
                    window.close();
                startButton.handleEvent(temp, window);
                stopButton.handleEvent(temp, window);
            }
        }

        update();
        render();
    }
}

void Game::update() {
    float deltaTime = timer.restart().asSeconds();
    if (currentState == State::Spinning) {
        drum1.update(deltaTime);
        drum2.update(deltaTime);
        drum3.update(deltaTime);

        if (drum1.isStopped() && drum2.isStopped() && drum3.isStopped()) {
            calculateWin();
            currentState = State::Win;
            timer.restart();
        }
    }
    else if (currentState == State::Win) {
        if (timer.getElapsedTime().asSeconds() >= 3) {
            currentState = State::Idle;
        }
    }
}

void Game::calculateWin() {
    int s1 = drum1.getCurrentSymbol();
    int s2 = drum2.getCurrentSymbol();
    int s3 = drum3.getCurrentSymbol();
    if (s1 == s2 && s2 == s3) {
        winAmount = 100;
    }
    else if (s1 == s2 || s2 == s3 || s1 == s3) {
        winAmount = 50;
    }
    else {
        winAmount = 0;
    }
}

void Game::render() {
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(1000, 600));
    background.setFillColor(sf::Color::White);

    window.clear();
    window.draw(background);
    drum1.draw(window);
    drum2.draw(window);
    drum3.draw(window);
    startButton.draw(window);
    stopButton.draw(window);
    window.display();
}