// Obstacle.h
#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
protected:
    sf::RectangleShape shape;

public:
Obstacle();
    virtual void update();
    virtual void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
};