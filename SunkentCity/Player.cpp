#include "Player.h"

Player::Player() : speed(300.f) {
    texture.loadFromFile("assets/diver.png");
    sprite.setTexture(texture);
    sprite.setPosition(100.f, 300.f);
    float targetWidth = 100.0f;
    float targetHeight = 100.0f;
    sprite.setScale(
        targetWidth / sprite.getLocalBounds().width, 
        targetHeight / sprite.getLocalBounds().height
    );
    sf::FloatRect bounds = sprite.getLocalBounds();
sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::update(float dt) {
    sf::Vector2f pos = sprite.getPosition();
    float boundsW = sprite.getGlobalBounds().width;
    float boundsH = sprite.getGlobalBounds().height;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    sprite.move(0, -speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  sprite.move(0, speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  sprite.move(-speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) sprite.move(speed * dt, 0);
    sf::Vector2f newPos = sprite.getPosition();

    // Bloquer à gauche et à droite (0 à 800)
    if (newPos.x < 0) newPos.x = 0;
    if (newPos.x + boundsW > 800) newPos.x = 800 - boundsW;

    // Bloquer en haut et en bas (0 à 600)
    if (newPos.y < 0) newPos.y = 0;
    if (newPos.y + boundsH > 600) newPos.y = 600 - boundsH;

    sprite.setPosition(newPos);
}
// Dans Player.cpp et Obstacle.cpp (Constructeur)




void Player::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Player::getBounds() const { return sprite.getGlobalBounds(); }