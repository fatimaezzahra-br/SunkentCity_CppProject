#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

enum class ObstacleType
{
    DAMAGE,
    BONUS
};

class Obstacle
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    ObstacleType type;

public:
    Obstacle(float x, float y);

    void update(float dt, float gameSpeed);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getHitbox() const;
    sf::Vector2f getPosition() const;

    void setType(ObstacleType t);
    ObstacleType getType() const;
};

#endif