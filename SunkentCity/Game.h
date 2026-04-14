#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.h"
#include "Player.h"

class Game {
public:
   Game(sf::RenderWindow& existingWindow);
    ~Game();
    void run();

private:
bool isGameOver; // Ajoute ceci
    sf::Text gameOverText;
int score; // <--- AJOUTE CECI
    sf::Text scoreText;
    void update();
    void render();

   sf::RenderWindow& window;
    AssetManager assets;
    Player* player;
    sf::Music music;
    sf::Clock clock;
    float timeLeft;

    // Objets pour le Menu et le Jeu
    sf::Texture menuTex;
    sf::Sprite menuSprite;
    sf::Texture backTex;
    sf::Sprite backSprite;

    bool isMenu; // Variable cruciale pour basculer entre menu et jeu
    std::vector<Obstacle*> obstacles;
sf::Clock obstacleClock;
};

#endif