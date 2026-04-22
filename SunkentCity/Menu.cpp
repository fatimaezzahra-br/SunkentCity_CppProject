

#include "Menu.h"

Menu::Menu() : isShowingAbout(false) { // Initialisation du booléen
    // 1. Chargement via le manager
    assets.loadTexture("bg", "assets/menu.png");
    assets.loadFont("mainFont", "assets/Fonts/arial.ttf");

    // 2. Configuration du Background
    backgroundSprite.setTexture(assets.getTexture("bg"));
    backgroundSprite.setScale(800.f / assets.getTexture("bg").getSize().x, 
                               600.f / assets.getTexture("bg").getSize().y);

    // 3. Configuration des Textes
    sf::Font& f = assets.getFont("mainFont");

    title.setFont(f);
    title.setString("SUNKEN CITY ESCAPE");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(150, 50);

    playText.setFont(f);
    playText.setString("1 - JOUER");
    playText.setPosition(300, 250);

    aboutText.setFont(f);
    aboutText.setString("2 - A PROPOS");
    aboutText.setPosition(300, 320);

    quitText.setFont(f);
    quitText.setString("3 - QUITTER");
    quitText.setPosition(300, 390);

    // 4. Configuration de la section "A PROPOS" (Overlay)
    overlay.setSize(sf::Vector2f(700.f, 450.f));
    overlay.setFillColor(sf::Color(0, 0, 50, 230)); // Bleu nuit transparent
    overlay.setOutlineThickness(2);
    overlay.setOutlineColor(sf::Color::Cyan);
    overlay.setPosition(50, 75);

    aboutDescription.setFont(f);
    aboutDescription.setCharacterSize(18);
    aboutDescription.setFillColor(sf::Color::White);
    aboutDescription.setString(
        "       --- SUNKEN CITY ESCAPE ---\n\n"
        "HISTOIRE :\n"
        "Marrakech est engloutie. En tant que dernier survivant,\n"
        "rejoignez le bunker avant la fin du temps imparti !\n\n"
        "COMMANDES :\n"
        "- FLECHES : Se deplacer dans l'eau\n"
        "- EVITER : Les poissoins dangerouxs et les obstacles marins\n"
        "- SCORE : Augmente avec le temps survécu, et les bonus collectes\n\n"
        "PROJET FSSM - Informatique 2026\n\n"
        "Dev par Fatima Ezzahra El Barbouchi & Amina ELMountassir\n\n"
        "      [ Appuyez sur ECHAP pour revenir au menu  ]"
    );
    aboutDescription.setPosition(80, 110);
}

int Menu::show(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (e.type == sf::Event::KeyPressed) {
                if (isShowingAbout) {
                    // Si on est dans le "A Propos", on n'écoute que Echap pour sortir
                    if (e.key.code == sf::Keyboard::Escape) isShowingAbout = false;
                } else {
                    // Touches normales du menu
                    if (e.key.code == sf::Keyboard::Num1) return 1; // Lancer le jeu
                    if (e.key.code == sf::Keyboard::Num2) isShowingAbout = true; // Ouvrir A Propos
                    if (e.key.code == sf::Keyboard::Num3) return 0; // Quitter
                }
            }
        }

        window.clear();
        
        // --- DESSIN DU MENU DE BASE ---
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(playText);
        window.draw(aboutText);
        window.draw(quitText);

        // --- DESSIN DE L'OVERLAY (Si activé) ---
        if (isShowingAbout) {
            window.draw(overlay);
            window.draw(aboutDescription);
        }

        window.display();
    }
    return 0;
}