

#include "Game.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include "Constants.h"

// ===================== CONSTRUCTOR =====================
Game::Game(sf::RenderWindow& win)
    : window(win),
      score(0.f),
      gameTimer(MAX_TIME),
      maxTime(MAX_TIME),
      gameSpeed(START_SPEED),
      level(1),
      hasKey(false),
      isGameOver(false),
      isWin(false),
      returnToMenu(false),
      waitingForNextLevel(false),
      winSoundPlayed(false),
      gameOverSoundPlayed(false)
{
    
    // 🎵 MUSIC
    if (!gameMusic.openFromFile("assets/make-a-music-game-in-sunknetcity--with-ambinece-for-kids-_042026.mp3"))
        std::cout << "❌ Music error: " << MUSIC_PATH << std::endl;
    else
        std::cout << "✅ Music loaded\n";

    gameMusic.setLoop(true);
    gameMusic.setVolume(100);
    gameMusic.play();

    // 🔊 WIN SOUND
    if (!winBuffer.loadFromFile("assets/winsongs.mp3"))
        std::cout << "❌ Win sound error\n";
    winSound.setBuffer(winBuffer);
    winSound.setVolume(100);

    // 🔊 GAME OVER SOUND
    if (!gameOverBuffer.loadFromFile("assets/game_over.mp3"))
        std::cout << "❌ GameOver sound error\n";
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(100);

    // 🌊 BACKGROUND
    // 🌊 BACKGROUND
if (!backgroundTex.loadFromFile(LEVEL1_BACKGROUND))
    std::cout << "Background error\n";

bg1.setTexture(backgroundTex);
bg2.setTexture(backgroundTex);

// scale pour remplir écran
float scaleX = window.getSize().x / (float)backgroundTex.getSize().x;
float scaleY = window.getSize().y / (float)backgroundTex.getSize().y;

bg1.setScale(scaleX, scaleY);
bg2.setScale(scaleX, scaleY);

// position côte à côte
bg1.setPosition(0, 0);
bg2.setPosition(bg1.getGlobalBounds().width, 0);
    // 👤 PLAYER
    player = std::make_unique<Player>();
    player->setPosition(50.f, 300.f);

    // 📝 FONT
    font.loadFromFile("assets/Fonts/arial.ttf");

    uiText.setFont(font);
    uiText.setCharacterSize(22);
    uiText.setFillColor(sf::Color::White);
}

// ===================== DESTRUCTOR =====================
Game::~Game()
{
    gameMusic.stop();
}

// ===================== RUN =====================
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
        }

        float dt = clock.restart().asSeconds();

        if (!isGameOver)
            update(dt);

        render();

        if (returnToMenu)
            return;
    }
}

// ===================== UPDATE =====================
void Game::update(float dt)
{
    if (justChangedLevel)
{
    justChangedLevel = false;
    return;
}
    float bgSpeed = 100.f; // vitesse du fond

bg1.move(-bgSpeed * dt, 0);
bg2.move(-bgSpeed * dt, 0);

// boucle infinie
if (bg1.getPosition().x + bg1.getGlobalBounds().width < 0)
{
    bg1.setPosition(bg2.getPosition().x + bg2.getGlobalBounds().width, 0);
}

if (bg2.getPosition().x + bg2.getGlobalBounds().width < 0)
{
    bg2.setPosition(bg1.getPosition().x + bg1.getGlobalBounds().width, 0);
}
    // ⛔ attendre ENTER pour level 2
    if (waitingForNextLevel)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            level = 2;
            gameTimer = MAX_TIME;
            hasKey = false;
            gameSpeed += SPEED_INCREMENT;

            backgroundTex.loadFromFile(LEVEL2_BACKGROUND);
           bg1.setTexture(backgroundTex);
bg2.setTexture(backgroundTex);
justChangedLevel = true;
            waitingForNextLevel = false;
        }
        return;
    }

    gameTimer -= dt;
    score += dt * SCORE_RATE;

    // ⏱ FIN TEMPS
    if (gameTimer <= 0)
    {
        if (level == 1)
        {
            waitingForNextLevel = true;
            return;
        }
        else if (level == 2)
{
    isGameOver = true;
    reachedBunker = true;
    isWin = true;
    gameMusic.stop();
}
    }

    player->update(dt);


       int rate = (level == 2) ? SPAWN_RATE_LEVEL_2 : SPAWN_RATE_LEVEL_1;

if (rand() % 100 < rate)
{
    float y = rand() % (SPAWN_Y_MAX - SPAWN_Y_MIN) + SPAWN_Y_MIN;

    int r = rand() % 4;
    ObstacleType t;

    if (r == 0) t = ObstacleType::BONUS;
    else if (r == 1) t = ObstacleType::DAMAGE;
    else if (r == 2) t = ObstacleType::DAMAGE;
    else t = ObstacleType::SCORE;

    auto o = std::make_unique<Obstacle>(SPAWN_X, y, t);

    obstacles.push_back(std::move(o));
}

    // ===================== COLLISION =====================
    for (int i = obstacles.size() - 1; i >= 0; i--)
    {
        obstacles[i]->update(dt, gameSpeed);

        if (player->getHitbox().intersects(obstacles[i]->getHitbox()))
        {
            if (obstacles[i]->getType() == ObstacleType::DAMAGE)
            {
                isGameOver = true;
                isWin = false;
                gameMusic.stop();
            }
            else if (obstacles[i]->getType() == ObstacleType::BONUS)
            {
                if (level == 2){
                    hasKey = true;
                      isWin = true; // toujours victoire au level 2
  
            }}
            else if (obstacles[i]->getType() == ObstacleType::SCORE)
            {
                score += 50.f;
            }

            obstacles.erase(obstacles.begin() + i);
            continue;
        }

        if (obstacles[i]->getPosition().x < -100)
        {
            obstacles.erase(obstacles.begin() + i);
        }
    }
}

// ===================== RENDER =====================
 void Game::render()
{
    window.clear();
   window.draw(bg1);
window.draw(bg2);

    for (auto& o : obstacles)
        o->draw(window);

    player->draw(window);

    // ===== TIMER BAR =====
    float barW = 300.f;
    float x = (window.getSize().x - barW) / 2.f;

    float progress = std::max(0.f, gameTimer / maxTime);

    sf::RectangleShape bg(sf::Vector2f(barW, 20));
    bg.setPosition(x, 20);
    bg.setFillColor(sf::Color(80, 80, 80));

    sf::RectangleShape bar(sf::Vector2f(barW * progress, 20));
    bar.setPosition(x, 20);

    if (progress > 0.6f)
        bar.setFillColor(sf::Color::Green);
    else if (progress > 0.3f)
        bar.setFillColor(sf::Color::Yellow);
    else
        bar.setFillColor(sf::Color::Red);

    window.draw(bg);
    window.draw(bar);

    // ===== UI TEXT =====
    std::stringstream ss;
    ss << "LEVEL: " << level
       << "\nTIME: " << (int)gameTimer
       << "\nSCORE: " << (int)score
       << "\nKEY: " << (hasKey ? "YES" : "NO");

    uiText.setString(ss.str());
    uiText.setPosition(20, 60);
    window.draw(uiText);

    // ===== MESSAGE LEVEL 2 =====
    if (waitingForNextLevel)
    {
        sf::Text msg;
        msg.setFont(font);
        msg.setCharacterSize(30);
        msg.setFillColor(sf::Color::Yellow);

        msg.setString("FELICITATION !\nAppuyez sur ENTREE\npour passer au LEVEL 2");

        sf::FloatRect b = msg.getLocalBounds();
        msg.setOrigin(b.width / 2, b.height / 2);
        msg.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        window.draw(msg);
    }

    // ===== GAME OVER =====
   
    if (isGameOver)
{
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(40);

    if (isWin)
    {
        msg.setString("Bravo !! vous avez rejoigne le bunker  !");
        msg.setFillColor(sf::Color::Green);

        // 🔊 WIN SOUND (STOP MUSIC + PLAY ONCE)
        if (!winSoundPlayed)
        {
            gameMusic.stop();
            winSound.play();
            winSoundPlayed = true;
        }
    }
    else
    {
        msg.setString("GAME OVER");
        msg.setFillColor(sf::Color::Red);

        // 🔊 GAME OVER SOUND
        if (!gameOverSoundPlayed)
        {
            gameMusic.stop();
            gameOverSound.play();
            gameOverSoundPlayed = true;
        }
    }

    window.draw(msg);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        returnToMenu = true;
}
window.display();}

 