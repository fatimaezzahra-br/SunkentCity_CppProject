#include "Obstacle.h"

Obstacle::Obstacle() {
    shape.setSize({60.f, 60.f});      // Un peu plus grand
    shape.setFillColor(sf::Color::Red);
    // On le met à 1200 au lieu de 800 pour qu'il soit déjà visible à l'écran
    shape.setPosition(800.f, 400.f); 
}

void Obstacle::update()
{
    // Réduis la vitesse à -2.f pour bien voir s'il bouge au début
    shape.move(-2.f, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Obstacle::getBounds()
{
    return shape.getGlobalBounds();
}