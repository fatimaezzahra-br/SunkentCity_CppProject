#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Obstacle(float x, float y);
    void update(float dt, float gameSpeed);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getHitbox() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    // On réduit la boîte de 10 pixels de chaque côté
    return sf::FloatRect(bounds.left + 10, bounds.top + 10, bounds.width - 20, bounds.height - 20);
}
};
#endif