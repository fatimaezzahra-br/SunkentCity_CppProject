#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(float x, float y)
{
    if (!texture.loadFromFile("assets/fish1.jpg"))
    {
        std::cerr << "Erreur texture obstacle" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    type = ObstacleType::DAMAGE;

    float size = 50.f;

    sprite.setScale(
        size / sprite.getLocalBounds().width,
        size / sprite.getLocalBounds().height
    );
}

void Obstacle::update(float dt, float gameSpeed)
{
    sprite.move(-gameSpeed * dt, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Obstacle::getHitbox() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Obstacle::getPosition() const
{
    return sprite.getPosition();
}

void Obstacle::setType(ObstacleType t)
{
    type = t;
}

ObstacleType Obstacle::getType() const
{
    return type;
}