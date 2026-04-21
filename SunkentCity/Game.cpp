/*#include "Game.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include"Constants.h"
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
      returnToMenu(false)
{
    // 🎵 MUSICSFML-2.6.2/SunkentCity/
    if (!winBuffer.loadFromFile("assets/winsongs.mp3"))
    std::cout << "Erreur chargement son WIN\n";

winSound.setBuffer(winBuffer);
if (!gameOverBuffer.loadFromFile("assets/gameover.wav"))
    std::cout << "Erreur chargement game over\n";
gameOverSound.setBuffer(gameOverBuffer);

// reset
winSoundPlayed = false;
gameOverSoundPlayed = false;
    if (!gameMusic.openFromFile(MUSIC_PATH))
        std::cout << "Music error\n";

    gameMusic.setLoop(true);
    gameMusic.play();

    // 🌊 BACKGROUND LEVEL 1
    if (!backgroundTex.loadFromFile(LEVEL1_BACKGROUND))
        std::cout << "Background error\n";

    backgroundSprite.setTexture(backgroundTex);
    backgroundSprite.setScale(
        window.getSize().x / (float)backgroundTex.getSize().x,
        window.getSize().y / (float)backgroundTex.getSize().y
    );
    if (!gameMusic.openFromFile(MUSIC_PATH))
{
    std::cout << "❌ Music error: " << MUSIC_PATH << std::endl;
}
else
{
    std::cout << "✅ Music loaded successfully\n";
}
gameMusic.setLoop(true);
gameMusic.setVolume(100); // 🔊 IMPORTANT
gameMusic.play();
if (!winBuffer.loadFromFile(WIN_SOUND_PATH))
{
    std::cout << "❌ Win sound error\n";
}
else
{
    std::cout << "✅ Win sound loaded\n";
}
winSound.setBuffer(winBuffer);
winSound.setVolume(100);
if (!gameOverBuffer.loadFromFile(GAMEOVER_SOUND_PATH))
{
    std::cout << "❌ GameOver sound error\n";
}
else
{
    std::cout << "✅ GameOver sound loaded\n";
}
gameOverSound.setBuffer(gameOverBuffer);
gameOverSound.setVolume(100);
    // 👤 PLAYER
    player = std::make_unique<Player>();
    player->setPosition(50.f, 300.f);

    // 📝 FONT
    font.loadFromFile(FONT_PATH);

    uiText.setFont(font);
    uiText.setCharacterSize(22);
    uiText.setFillColor(sf::Color::White);
}

// ===================== DESTRUCTOR =====================
Game::~Game()
{
    gameMusic.stop();
    obstacles.clear();
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
    if (waitingForNextLevel)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        // 👉 passer au level 2
        level = 2;
        gameTimer = MAX_TIME;
        hasKey = false;
        gameSpeed += SPEED_INCREMENT;

        backgroundTex.loadFromFile(LEVEL2_BACKGROUND);
        backgroundSprite.setTexture(backgroundTex);

        waitingForNextLevel = false;
    }

    return; // ⛔ bloque le jeu
}
    gameTimer -= dt;
    score += dt * SCORE_RATE;

    // 💀 GAME OVER si joueur mort (si tu gardes life ailleurs)

if (gameTimer <= 0)
{
    if (level == 1 && !waitingForNextLevel)
    {
        // ⛔ pause + message
        waitingForNextLevel = true;
        return;
    }

    else if (level == 2)
    {
        if (hasKey)
        {
            isWin = true;
            isGameOver = true;
            gameMusic.stop();
        }
        else
        {
            isWin = false;
            isGameOver = true;
            gameMusic.stop();
        }
    }
}

    player->update(dt);

    // ===================== SPAWN OBSTACLES =====================
    int rate = (level == 2) ? SPAWN_RATE_LEVEL_2 : SPAWN_RATE_LEVEL_1;

    if (rand() % 100 < rate)
    {
        float y = rand() % (SPAWN_Y_MAX - SPAWN_Y_MIN) + SPAWN_Y_MIN;

      ObstacleType t;

int r = rand() % 3;
if (r == 0) t = ObstacleType::BONUS;
else if (r == 1) t = ObstacleType::DAMAGE;
else t = ObstacleType::SCORE;

auto o = std::make_unique<Obstacle>(SPAWN_X, y, t);

     
        if (r == 0) o->setType(ObstacleType::BONUS);
        else if (r == 1) o->setType(ObstacleType::DAMAGE);
        else o->setType(ObstacleType::SCORE);

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
    isWin = false;        // 💀 FORCE GAME OVER
    gameMusic.stop();
}
            else if (obstacles[i]->getType() == ObstacleType::BONUS)
            {
                if (level == 2)
                    hasKey = true;
            }
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
    window.draw(backgroundSprite);

    for (auto& o : obstacles)
        o->draw(window);

    player->draw(window);

    // ===================== TIMER BAR (ONLY ONE BAR) =====================
    float barW = 300.f;
    float x = (window.getSize().x - barW) / 2.f;

    float progress = gameTimer / maxTime;
    progress = std::max(0.f, progress);

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

    // ===================== UI TEXT =====================
    std::stringstream ss;
    ss << "LEVEL: " << level
       << "\nTIME: " << (int)gameTimer
       << "\nSCORE: " << (int)score
       << "\nKEY: " << (hasKey ? "YES" : "NO");

    uiText.setString(ss.str());
    uiText.setPosition(20, 60);

    window.draw(uiText);
    //nextlevel
    if (waitingForNextLevel)
{
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(30);
    msg.setFillColor(sf::Color::Yellow);

    msg.setString(" Felicitation \nAppuyez sur ENTREE\npour passer au LEVEL 2");

    sf::FloatRect b = msg.getLocalBounds();
    msg.setOrigin(b.width / 2, b.height / 2);
    msg.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.draw(msg);
}

    // ===================== GAME OVER =====================
    if (isGameOver)
{
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(40);

    if (isWin)
    {
        msg.setString("YOU WIN !");
        msg.setFillColor(sf::Color::Green);

        // 🔊 WIN SOUND
        if (!winSoundPlayed)
        {
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
            gameOverSound.play();
            gameOverSoundPlayed = true;
        }
    }

    sf::FloatRect b = msg.getLocalBounds();
    msg.setOrigin(b.width / 2, b.height / 2);
    msg.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.draw(msg);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        returnToMenu = true;
}
window.display();}
*/
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
    if (!winBuffer.loadFromFile("assets/win.wav"))
        std::cout << "❌ Win sound error\n";
    winSound.setBuffer(winBuffer);
    winSound.setVolume(100);

    // 🔊 GAME OVER SOUND
    if (!gameOverBuffer.loadFromFile("assets/gameover.wav"))
        std::cout << "❌ GameOver sound error\n";
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(100);

    // 🌊 BACKGROUND
    if (!backgroundTex.loadFromFile(LEVEL1_BACKGROUND))
        std::cout << "Background error\n";

    backgroundSprite.setTexture(backgroundTex);
    backgroundSprite.setScale(
        window.getSize().x / (float)backgroundTex.getSize().x,
        window.getSize().y / (float)backgroundTex.getSize().y
    );

    // 👤 PLAYER
    player = std::make_unique<Player>();
    player->setPosition(50.f, 300.f);

    // 📝 FONT
    font.loadFromFile(FONT_PATH);

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
            backgroundSprite.setTexture(backgroundTex);

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
            isWin = hasKey;
            gameMusic.stop();
        }
    }

    player->update(dt);

    // ===================== SPAWN =====================
    int rate = (level == 2) ? SPAWN_RATE_LEVEL_2 : SPAWN_RATE_LEVEL_1;

    if (rand() % 100 < rate)
    {
        float y = rand() % (SPAWN_Y_MAX - SPAWN_Y_MIN) + SPAWN_Y_MIN;

        int r = rand() % 3;
        ObstacleType t;

        if (r == 0) t = ObstacleType::BONUS;
        else if (r == 1) t = ObstacleType::DAMAGE;
        else t = ObstacleType::SCORE;

   
if (r == 0) t = ObstacleType::BONUS;
else if (r == 1) t = ObstacleType::DAMAGE;
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
                if (level == 2)
                    hasKey = true;
            }
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
    window.draw(backgroundSprite);

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
        msg.setString("YOU WIN !");
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