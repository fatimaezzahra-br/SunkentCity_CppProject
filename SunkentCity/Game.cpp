#include "Game.h"
#include <iostream>
#include <sstream>

// Constructeur
Game::Game(sf::RenderWindow& win) 
    : window(win), score(0.f), gameTimer(60.f), isGameOver(false), gameSpeed(250.f) 
{
    if (!gameMusic.openFromFile("assets/saturn-3-music-underwater-whale-and-diving-sound-ambient-116185.mp3")) {
        std::cerr << "Erreur : Impossible de charger la musique !" << std::endl;
    } else {
        gameMusic.setLoop(true);  // La musique recommence à la fin
        gameMusic.setVolume(50); // Volume entre 0 et 100
        gameMusic.play();        // Lancer la musique
    }
    // Arrête la musique au crash

    // 1. Chargement du fond
    if (!backgroundTex.loadFromFile("assets/water2.jpg")) {
        std::cerr << "Erreur : Impossible de charger assets/water2.jpg" << std::endl;
    } else {
        backgroundTex.setSmooth(true);
        backgroundSprite.setTexture(backgroundTex);
        
        sf::Vector2u size = backgroundTex.getSize();
        backgroundSprite.setScale(800.f / size.x, 600.f / size.y);
    }

    // 2. Initialisation des entités
  obstacles.clear();
    player = new Player();
    
    // POSITION DE SECURITE : On force le joueur a gauche (x=50) au milieu (y=300)
    // pour qu'il ne touche aucun obstacle qui apparaitrait par erreur
    player->setPosition(50.f, 300.f); 

    // 3. Interface UI
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cerr << "Erreur : Police arial.ttf introuvable !" << std::endl;
    }

    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(20, 20);
}

Game::~Game() {
    delete player;
    for (auto obs : obstacles) {
        delete obs;
    }
    obstacles.clear();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                return;
            }
        }

        float dt = clock.restart().asSeconds();

        if (!isGameOver) {
            update(dt);
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                return;
            }
        }
        render();
    }
}

void Game::update(float dt) {
    gameTimer -= dt;
    score += dt * 10.f;
    gameSpeed += dt * 2.f;

    if (gameTimer <= 0) {
        gameTimer = 0;
        isGameOver = true;
    }

    player->update(dt);

    // --- CORRECTION APPARITION ---
    if (rand() % 100 < 2) { 
        float spawnX = 1000.f; // On le cree tres loin a droite (hors ecran)
        float randomY = static_cast<float>(rand() % 500 + 50);
        obstacles.push_back(new Obstacle(spawnX, randomY)); // On utilise bien spawnX
    }

    // --- CORRECTION COLLISIONS ---
    for (int i = obstacles.size() - 1; i >= 0; i--) {
        obstacles[i]->update(dt, gameSpeed);

        // On ne teste la collision que si l'obstacle est entre dans l'ecran (x < 800)
        if (obstacles[i]->getPosition().x < 800) { 
            if (player->getBounds().intersects(obstacles[i]->getBounds())) {
                isGameOver = true;
            }
        }
if (player->getHitbox().intersects(obstacles[i]->getHitbox())) {
    isGameOver = true;
    gameMusic.stop(); // Arrête la musique au crash
}
        if (obstacles[i]->getPosition().x < -100) {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
    }
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);

    for (auto obs : obstacles) {
        obs->draw(window);
    }
    player->draw(window);
   // sf::RectangleShape pDebug;
   /*sf::FloatRect pHit = player->getHitbox(); 
    pDebug.setPosition(pHit.left, pHit.top);
    pDebug.setSize({pHit.width, pHit.height});
    pDebug.setFillColor(sf::Color::Transparent);
    pDebug.setOutlineColor(sf::Color::Red);
    pDebug.setOutlineThickness(2);
    window.draw(pDebug);
    for (auto obs : obstacles) {
        sf::RectangleShape oDebug;
        sf::FloatRect oHit = obs->getHitbox();
        oDebug.setPosition(oHit.left, oHit.top);
        oDebug.setSize({oHit.width, oHit.height});
        oDebug.setFillColor(sf::Color::Transparent);
        oDebug.setOutlineColor(sf::Color::Yellow);
        oDebug.setOutlineThickness(2);
        window.draw(oDebug);
    }
        */


    std::stringstream ss;
    ss << "Bunker dans : " << (int)gameTimer << "s\n"
       << "Score : " << (int)score;
    uiText.setString(ss.str());
    window.draw(uiText);

    if (isGameOver) {
        sf::Text endMsg;
        endMsg.setFont(font);
        endMsg.setCharacterSize(40);
        endMsg.setFillColor(sf::Color::Yellow);
        
        if (gameTimer <= 0) 
            endMsg.setString("VICTOIRE ! MARRAKECH SAUVEE\nAppuyez sur Entree");
        else 
            endMsg.setString("GAME OVER !\nAppuyez sur Entree");
        
        endMsg.setPosition(150, 250);
        window.draw(endMsg);
    }
    window.display();
}