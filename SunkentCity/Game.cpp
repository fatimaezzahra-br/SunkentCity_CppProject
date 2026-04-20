/* 
#include "Game.h"
#include <iostream>
#include <sstream>

// Constructeur
Game::Game(sf::RenderWindow& win) 
    : window(win), score(0.f), gameTimer(60.f), isGameOver(false), gameSpeed(250.f) 
{
    if (!gameMusic.openFromFile("assets/make-a-music-game-in-sunknetcity--with-ambinece-for-kids-_042026.mp3")) {
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
  distance += 100 * dt;// vitesse progression
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
       // Barre fond (gris)
/* sf::RectangleShape barBg;//
barBg.setSize({300, 20});
barBg.setFillColor(sf::Color(100, 100, 100));
barBg.setPosition({20, 20});

// Barre progression (verte)
sf::RectangleShape bar;
float progress = 1.f - (gameTimer / maxTime);
if (progress > 1.f) progress = 1.f;

bar.setSize({300 * progress, 20});
bar.setFillColor(sf::Color::Green);
bar.setPosition({20, 20});

// Dessin
window.draw(barBg);
window.draw(bar);
if (distance >= maxDistance)
{
    std::cout << "WIN!" << std::endl;
    window.close();
}


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
    */
#include "Game.h"
#include <iostream>
#include <sstream>

// =====================
// CONSTRUCTEUR
// =====================
Game::Game(sf::RenderWindow& win)
    : window(win),
      score(0.f),
      gameTimer(60.f),
      maxTime(60.f),
      gameSpeed(250.f),
      isGameOver(false),
      returnToMenu(false)
{
    // 🎵 musiqueSFML-SFML-2.6.2/SunkentCity/
    if (!gameMusic.openFromFile("assets/make-a-music-game-in-sunknetcity--with-ambinece-for-kids-_042026.mp3")) {
        std::cerr << "Erreur musique !" << std::endl;
    } else {
        gameMusic.setLoop(true);
        gameMusic.setVolume(50);
        gameMusic.play();
    }

    // 🌊 background
    if (!backgroundTex.loadFromFile("assets/water2.jpg")) {
        std::cerr << "Erreur background !" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTex);

        sf::Vector2u size = backgroundTex.getSize();
        backgroundSprite.setScale(
            window.getSize().x / (float)size.x,
            window.getSize().y / (float)size.y
        );
    }

    // 👤 player
    player = new Player();
    player->setPosition(50.f, 300.f);

    // 📝 font
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cerr << "Erreur font !" << std::endl;
    }

    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
}

// =====================
// DESTRUCTEUR
// =====================
Game::~Game()
{
    delete player;
    for (auto o : obstacles)
        delete o;
}

// =====================
// RUN LOOP
// =====================
void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed &&
                e.key.code == sf::Keyboard::Escape)
            {
                returnToMenu = true;
                return;
            }
        }

        float dt = clock.restart().asSeconds();

        if (!isGameOver)
            update(dt);

        render();

        if (returnToMenu)
            return;
    }
}

// =====================
// UPDATE
// =====================
void Game::update(float dt)
{
    gameTimer -= dt;
    score += dt * 10.f;
    gameSpeed += dt * 2.f;

    if (gameTimer <= 0)
    {
        gameTimer = 0;
        isGameOver = true;
        gameMusic.stop();
    }

    player->update(dt);

    // 🎲 spawn obstacles
    if (rand() % 100 < 2)
    {
        float y = rand() % 500 + 50;
        obstacles.push_back(new Obstacle(1000.f, y));
    }

    // 🔄 obstacles update
    for (int i = obstacles.size() - 1; i >= 0; i--)
    {
        obstacles[i]->update(dt, gameSpeed);

        if (player->getHitbox().intersects(obstacles[i]->getHitbox()))
        {
            isGameOver = true;
            gameMusic.stop();
        }

        if (obstacles[i]->getPosition().x < -100)
        {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
    }
}

// =====================
// RENDER
// =====================
void Game::render()
{
    window.clear();

    window.draw(backgroundSprite);

    for (auto o : obstacles)
        o->draw(window);

    player->draw(window);

    // =====================
    // BARRE PROGRESSION
    // =====================
    float barWidth = 300.f;
    float barHeight = 20.f;

    float posX = (window.getSize().x - barWidth) / 2.f;

    sf::RectangleShape barBg({barWidth, barHeight});
    barBg.setPosition(posX, 20);
    barBg.setFillColor(sf::Color(100, 100, 100));

    float progress = 1.f - (gameTimer / maxTime);
    if (progress < 0) progress = 0;
    if (progress > 1) progress = 1;

    sf::RectangleShape bar({barWidth * progress, barHeight});

    if (progress < 0.5)
        bar.setFillColor(sf::Color::Green);
    else if (progress < 0.8)
        bar.setFillColor(sf::Color::Yellow);
    else
        bar.setFillColor(sf::Color::Red);

    bar.setPosition(posX, 20);

    window.draw(barBg);
    window.draw(bar);

    // =====================
    // UI TEXT
    // =====================
    int m = (int)gameTimer / 60;
    int s = (int)gameTimer % 60;

    std::stringstream ss;
    ss << "Temps : " << m << ":"
       << (s < 10 ? "0" : "") << s
       << "\nScore : " << (int)score;

    uiText.setString(ss.str());
    uiText.setPosition(20, 60);

    window.draw(uiText);

    // =====================
    // GAME OVER / WIN
    // =====================
    if (isGameOver)
    {
        sf::Text msg;
        msg.setFont(font);
        msg.setCharacterSize(40);
        msg.setFillColor(sf::Color::Yellow);

        if (gameTimer <= 0)
            msg.setString("FELICITATION !\nPASSER AU NIVEAU SUIVANT");
        else
            msg.setString("GAME OVER\nAppuyez sur Entree");

        sf::FloatRect bounds = msg.getLocalBounds();
        msg.setOrigin(bounds.width / 2, bounds.height / 2);
        msg.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        window.draw(msg);

        // ⬅ retour menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            returnToMenu = true;
        }
    }

    window.display();
}