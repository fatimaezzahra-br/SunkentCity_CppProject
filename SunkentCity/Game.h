#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Obstacle.h"
#include <SFML/Audio.hpp>

class Game {
private:
    // --- RÉFÉRENCES ET SYSTÈME ---
    sf::RenderWindow& window;
    sf::Music gameMusic;  // Référence à la fenêtre créée dans le main
    sf::Font font;             // Police pour le score et les messages
    sf::Text uiText;    
    sf::Texture backgroundTex;  // La texture reste en mémoire ici
    sf::Sprite backgroundSprite;       // Objet texte pour l'affichage écran
    
    // --- OBJETS DU JEU ---
    Player* player;                // Pointeur vers le joueur
    std::vector<Obstacle*> obstacles; // Liste dynamique d'obstacles

    // --- VARIABLES DE JEU (LOGIQUE) ---
    float score;         // Score actuel (basé sur le temps)
    float gameTimer;     // Compte à rebours avant le bunker (ex: 60s)
    float gameSpeed;     // Vitesse de défilement des obstacles
    bool isGameOver;     // État du jeu (Mort ou Victoire)

    // --- MÉTHODES PRIVÉES ---
    void initUI();       // Initialisation des textes
    void update(float dt); // Logique interne
    void render();       // Affichage interne

public:
    /**
     * @brief Constructeur
     * @param win Référence vers la fenêtre de rendu du main.cpp
     */
    Game(sf::RenderWindow& win);

    /**
     * @brief Destructeur
     * Libère la mémoire (Player et Obstacles)
     */
    ~Game();

    /**
     * @brief Boucle principale du jeu
     * Gère le DeltaTime, les événements et l'appel à update/render
     */
    void run();
};

#endif // GAME_H
