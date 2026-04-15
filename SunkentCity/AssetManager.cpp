// AssetManager.cpp
#include "AssetManager.h"
#include <iostream>

void AssetManager::loadTexture(std::string name, std::string fileName) {
    sf::Texture tex;
    if (tex.loadFromFile(fileName)) {
        textures[name] = tex;
    } else {
        std::cerr << "Erreur : Impossible de charger la texture " << fileName << std::endl;
    }
}

sf::Texture& AssetManager::getTexture(std::string name) {
    return textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string fileName) {
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        fonts[name] = font;
    } else {
        std::cerr << "Erreur : Impossible de charger la police " << fileName << std::endl;
    }
}

sf::Font& AssetManager::getFont(std::string name) {
    return fonts.at(name);
}