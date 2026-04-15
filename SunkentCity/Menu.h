#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Menu {
private:
    AssetManager assets; // Le manager est membre de la classe
    sf::Sprite backgroundSprite;
    
    // On déclare les textes ici pour plus de clarté
    sf::Text title;
    sf::Text playText;
    sf::Text quitText;
    sf::Text aboutText;
    bool isShowingAbout;          // Est-ce qu'on affiche l'onglet à propos ?
    sf::RectangleShape overlay;    // Fond sombre derrière le texte
    sf::Text aboutDescription;     // Le contenu du texte à propos
    sf::Font font;

public:
    Menu();
    int show(sf::RenderWindow& window);
};

#endif