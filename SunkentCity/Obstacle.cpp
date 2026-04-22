#include "Obstacle.h"
#include <iostream>
#include <cstdlib> // pour rand()

// ===================== CONSTRUCTOR =====================
Obstacle::Obstacle(float x, float y, ObstacleType t)
{
    type = t;

    // ===================== TEXTURE BY TYPE =====================
    if (type == ObstacleType::BONUS)
    {
        if (!texture.loadFromFile("assets/key.jpg"))
            std::cout << "Error loading bonus texture\n";
    }
    else if (type == ObstacleType::DAMAGE)
    {
        // 🎯 2 types de DAMAGE (random)
        int r = rand() % 2;

        if (r == 0)
        {
            if (!texture.loadFromFile("assets/fish1.jpg"))
                std::cout << "Error loading fish1 texture\n";
        }
        else
        {
            if (!texture.loadFromFile("assets/fish2.jpg"))
                std::cout << "Error loading fish2 texture\n";
        }
    }
    else if (type == ObstacleType::SCORE)
    {
        if (!texture.loadFromFile("assets/coin.png"))
            std::cout << "Error loading coin texture\n";
    }
    else if (type == ObstacleType::SPEED)
    {
        if (!texture.loadFromFile("assets/speed.png"))
            std::cout << "Error loading speed texture\n";
    }
  
    
        // fallback (sécurité)
       

    // ===================== SPRITE SETUP =====================
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    // ===================== SCALE =====================
    float size = 50.f;

    sprite.setScale(
        size / sprite.getLocalBounds().width,
        size / sprite.getLocalBounds().height
    );
}

// ===================== UPDATE =====================
void Obstacle::update(float dt, float gameSpeed)
{
    // mouvement vers la gauche
    sprite.move(-gameSpeed * dt, 0.f);
}

// ===================== DRAW =====================
void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

// ===================== HITBOX =====================
sf::FloatRect Obstacle::getHitbox() const
{
    return sprite.getGlobalBounds();
}

// ===================== POSITION =====================
sf::Vector2f Obstacle::getPosition() const
{
    return sprite.getPosition();
}

// ===================== TYPE =====================
void Obstacle::setType(ObstacleType t)
{
    type = t;
}

ObstacleType Obstacle::getType() const
{
    return type;
}