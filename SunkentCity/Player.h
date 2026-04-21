#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

public:
    Player();

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getHitbox() const;

    void setPosition(float x, float y);
    void setColor(sf::Color color);
};

#endif
