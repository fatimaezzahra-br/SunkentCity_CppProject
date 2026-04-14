// Player.h
#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool onGround;

public:
    Player(sf::Texture& texture);

    void update();
    void jump();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};