
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Obstacle.h"
#include <memory>

class Game {
private:
    sf::RenderWindow& window;


std::unique_ptr<Player> player;
   std::vector<std::unique_ptr<Obstacle>> obstacles;

    sf::Texture backgroundTex;
   
sf::Sprite bg1;
sf::Sprite bg2;
    sf::Font font;
    sf::Text uiText;

    sf::Music gameMusic;
bool isWin = false;
    float score;
    float gameTimer;
    float maxTime;
    float gameSpeed;
   bool waitingForNextLevel = false; 
sf::SoundBuffer winBuffer;
sf::Sound winSound;
bool winSoundPlayed = false;
sf::SoundBuffer gameOverBuffer;
sf::Sound gameOverSound;


bool gameOverSoundPlayed = false;
    float life;
    float maxLife;
    bool hasKey;

    bool isGameOver;
    bool returnToMenu;
bool reachedBunker = false;
    int level;
bool justChangedLevel = false;
public:
    Game(sf::RenderWindow& win);
    ~Game();

    void run();
    void update(float dt);
    void render();

    bool isFinished() const { return returnToMenu; }
};
#endif