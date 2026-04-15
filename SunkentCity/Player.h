#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
public:
    Player();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    sf::FloatRect getHitbox() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float marginX = bounds.width * 0.2f;
    float marginY = bounds.height * 0.2f;
    // On réduit la boîte de 10 pixels de chaque côté
    return sf::FloatRect(bounds.left + 5, bounds.top + 5, bounds.width - 10, bounds.height - 10);
}
};
#endif
