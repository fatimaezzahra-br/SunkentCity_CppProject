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
    // On réduit la boîte de 10 pixels de chaque côté
    return sf::FloatRect(bounds.left + 10, bounds.top + 10, bounds.width - 20, bounds.height - 20);
}
};
#endif
