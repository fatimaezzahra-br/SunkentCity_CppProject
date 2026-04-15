#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    AssetManager() {}

    // Charge une texture et la nomme
    void loadTexture(std::string name, std::string fileName);
    sf::Texture& getTexture(std::string name);

    // Charge une police et la nomme
    void loadFont(std::string name, std::string fileName);
    sf::Font& getFont(std::string name);
};

#endif