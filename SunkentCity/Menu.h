#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Menu {
private:
    AssetManager assets; 
    sf::Sprite backgroundSprite;
    
    // On déclare les textes ici pour plus de clarté
    sf::Text title;
    sf::Text playText;
    sf::Text quitText;
    sf::Text aboutText;
    bool isShowingAbout;          
    sf::RectangleShape overlay;   
    sf::Text aboutDescription;     
    sf::Font font;

public:
    Menu();
    int show(sf::RenderWindow& window);
};

#endif