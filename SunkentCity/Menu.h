// Menu.h
/*#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    int show(sf::RenderWindow& window);
};
*/
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    // Retourne un entier pour savoir quelle action l'utilisateur a choisie
    int show(sf::RenderWindow& window);
};

#endif