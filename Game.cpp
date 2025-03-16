#include "Game.h"

Game::Game(sf::Texture* textures, int height, int number)
    : window(sf::VideoMode({ 1000, 600 }), "Slot Machine"),
    drum1(textures[0], height, number, 50, new Drum::Symbol[5] { 
            Drum::Symbol::Star,
            Drum::Symbol::Hexagon,
            Drum::Symbol::Heart,
            Drum::Symbol::Lightning,
            Drum::Symbol::Triangle
        }),
    drum2(textures[1], height, number, 50 + height, new Drum::Symbol[5]{
            Drum::Symbol::Triangle,
            Drum::Symbol::Hexagon,
            Drum::Symbol::Lightning,
            Drum::Symbol::Star,
            Drum::Symbol::Heart
        }),
    drum3(textures[2], height, number, 50 + height * 2, new Drum::Symbol[5]{
            Drum::Symbol::Lightning,
            Drum::Symbol::Hexagon,
            Drum::Symbol::Heart,
            Drum::Symbol::Star,
            Drum::Symbol::Triangle
        }),
    startButton(sf::Vector2f(700, 325), sf::Vector2f(200, 50), static_cast<std::string>("Start"), &font),
    stopButton(sf::Vector2f(700, 225), sf::Vector2f(200, 50), static_cast<std::string>("Stop"), &font),
    currentState(State::Idle) {
    startButton.setOnClick([this]() {
        if (currentState == State::Idle) {
            currentState = State::Spinning;
            srand(time(NULL));
            winAmount -= 25;
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
            currentState = State::Idle;
            calculateWin();
            timer.restart();
        }
    }
}

void Game::calculateWin() {
    Drum::Symbol s1 = drum1.getCurrentSymbol();
    Drum::Symbol s2 = drum2.getCurrentSymbol();
    Drum::Symbol s3 = drum3.getCurrentSymbol();
    if (s1 == s2 && s2 == s3) {
        winAmount += 500;
    }
    else if (s1 == s2 || s2 == s3 || s1 == s3) {
        winAmount += 50;
    }
}

void Game::render() {
    sf::RectangleShape background;
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(1000, 600));
    background.setFillColor(sf::Color::White);

    sf::Text score(font, static_cast<std::string>("Score: ") + std::to_string(winAmount));
    score.setPosition(sf::Vector2f( 225, 550));
    score.setFillColor(sf::Color::Black);
    score.setCharacterSize(24);


    window.clear();
    window.draw(background);
    drum1.draw(window);
    drum2.draw(window);
    drum3.draw(window);
    startButton.draw(window);
    stopButton.draw(window);
    window.draw(score);
    window.display();
}