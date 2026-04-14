// AssetManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class AssetManager {
public:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> sounds;
std::map<std::string, sf::Font> fonts;
    sf::Texture& getTexture(const std::string& name);
    sf::SoundBuffer& getSound(const std::string& name);
sf::Font& getFont(const std::string& name);
    void load();
};