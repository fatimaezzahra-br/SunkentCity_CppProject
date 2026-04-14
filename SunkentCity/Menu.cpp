// Menu.cpp
#include "Menu.h"
#include <iostream>

int Menu::show(sf::RenderWindow& window)
{
    sf::Texture backgroundTex;
    sf::Sprite backgroundSprite;
    
    // Chargement du fond
    if (!backgroundTex.loadFromFile("assets/water2.jpg")) {
        std::cerr << "ERREUR : Impossible de charger assets/water2.jpg" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTex);
    
    // Adaptation de la taille (800x600)
    backgroundSprite.setScale(
        800.f / backgroundSprite.getGlobalBounds().width, 
        600.f / backgroundSprite.getGlobalBounds().height
    );

    sf::Font font;
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cerr << "ERREUR : Police introuvable !" << std::endl;
    }

    // --- TEXTES DU MENU ---
    sf::Text title("SUNKEN CITY ESCAPE", font, 50);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(150, 80);

    sf::Text play("1 - Play", font, 30);
    play.setPosition(200, 220);

    sf::Text aboutText("2 - About", font, 30);
    aboutText.setPosition(200, 270);

    sf::Text quit("3 - Quit", font, 30);
    quit.setPosition(200, 320);

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            // Touche 1 : Lancer le jeu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                return 1;

            // Touche 3 : Quitter
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                return 0;

            // Touche 2 : À propos
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                bool inAbout = true;
                sf::Text info("Sunken City Escape\n\nVersion : 1.0\n\nAppuyez sur 'Echap' pour revenir", font, 20);
                info.setPosition(150, 220);

                while (inAbout && window.isOpen())
                {
                    sf::Event aboutEvent;
                    while (window.pollEvent(aboutEvent))
                    {
                        if (aboutEvent.type == sf::Event::Closed) window.close();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            inAbout = false;
                    }
                    window.clear();
                    window.draw(backgroundSprite);
                    window.draw(info);
                    window.display();
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(play);
        window.draw(aboutText);
        window.draw(quit);
        window.display();
    }
    return 0;
}