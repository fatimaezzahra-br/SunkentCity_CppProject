#include "Player.h"
#include <iostream>

Player::Player()
{
    speed = 300.f;

    if (!texture.loadFromFile("assets/diver.png"))
        std::cout << "Player texture error\n";

    sprite.setTexture(texture);
    sprite.setPosition(100.f, 300.f);

    float targetW = 100.f;
    float targetH = 100.f;

    sprite.setScale(
        targetW / sprite.getLocalBounds().width,
        targetH / sprite.getLocalBounds().height
    );

    // centre origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::update(float dt)
{
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        sprite.move(0, -speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        sprite.move(0, speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        sprite.move(-speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        sprite.move(speed * dt, 0);

    // LIMITS WINDOW (800x600)
    sf::Vector2f newPos = sprite.getPosition();

    if (newPos.x < 0) newPos.x = 0;
    if (newPos.x + bounds.width > 800) newPos.x = 800 - bounds.width;

    if (newPos.y < 0) newPos.y = 0;
    if (newPos.y + bounds.height > 600) newPos.y = 600 - bounds.height;

    sprite.setPosition(newPos);

    // reset color (après hit)
    sprite.setColor(sf::Color::White);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Player::getHitbox() const
{
    sf::FloatRect b = sprite.getGlobalBounds();

    float marginX = b.width * 0.2f;
    float marginY = b.height * 0.2f;

    return sf::FloatRect(
        b.left + marginX / 2,
        b.top + marginY / 2,
        b.width - marginX,
        b.height - marginY
    );
}

void Player::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Player::setColor(sf::Color color)
{
    sprite.setColor(color);
}