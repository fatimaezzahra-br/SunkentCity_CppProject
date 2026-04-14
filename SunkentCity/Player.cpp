// Player.cpp
#include "Player.h"
#include "Constants.h"

Player::Player(sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setPosition({100, 400});
    sprite.setColor(sf::Color::White);
    velocity = {0, 0};
    onGround = false;
}

void Player::update()
{
    velocity.y += GRAVITY;
    sprite.move(velocity);

    if (sprite.getPosition().y > 400) {
        sprite.setPosition(sprite.getPosition().x, 400);
        velocity.y = 0;
        onGround = true;
    }
}

void Player::jump()
{
    if (onGround) {
        velocity.y = JUMP_FORCE;
        onGround = false;
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Player::getBounds()
{
    return sprite.getGlobalBounds();
}