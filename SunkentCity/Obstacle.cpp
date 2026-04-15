#include "Obstacle.h"
#include <iostream>

// Le constructeur prend x et y pour savoir où faire apparaître l'obstacle
Obstacle::Obstacle(float x, float y) {
    // 1. Chargement de la texture (Idéalement via AssetManager, sinon en direct ici)
    if (!texture.loadFromFile("assets/fish1.jpg")) {
        // Si l'image n'est pas trouvée, on peut utiliser un rectangle de couleur
        std::cerr << "Erreur : Texture obstacle manquante !" << std::endl;
    }
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    // Optionnel : On peut ajuster la taille si l'image est trop grande
    // sprite.setScale(0.5f, 0.5f);
    float targetWidth = 50.0f; 
    float targetHeight = 50.0f;
    sprite.setScale(
        targetWidth / sprite.getLocalBounds().width, 
        targetHeight / sprite.getLocalBounds().height
    ); 
}

void Obstacle::update(float dt, float gameSpeed) {
    // 4. Gestion des obstacles (Apparition aléatoire)
    // Dans Player.cpp et Obstacle.cpp (Constructeur)
sf::FloatRect bounds = sprite.getLocalBounds();
sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // L'obstacle se déplace vers la gauche
    // gameSpeed est la vitesse de défilement du monde
    sprite.move(-gameSpeed * dt, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    // Retourne la zone de collision de l'obstacle
    return sprite.getGlobalBounds();
}

sf::Vector2f Obstacle::getPosition() const {
    return sprite.getPosition();
}
// Dans Player.cpp et Obstacle.cpp (Constructeur)
