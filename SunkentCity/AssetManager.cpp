// AssetManager.cpp
#include "AssetManager.h"

sf::Texture& AssetManager::getTexture(const std::string& name)
{
    return textures[name];
}

sf::SoundBuffer& AssetManager::getSound(const std::string& name)
{
    return sounds[name];
}

void AssetManager::load()
{
    textures["player"].loadFromFile("assets/person2.jpg");
    textures["key"].loadFromFile("assets/key.jpg");
    textures["bg"].loadFromFile("assets/background.jpg");

    sounds["jump"].loadFromFile("assets/freesound_community-underwater-waves-5983.mp3");
    sounds["hit"].loadFromFile("assets/freesound_community-underwater-waves-5983.mp3");
    fonts["arial"].loadFromFile("assets/Fonts/arial.ttf"); 
}
sf::Font& AssetManager::getFont(const std::string& name)
{
    return fonts[name];
}
