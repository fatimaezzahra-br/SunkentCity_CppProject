#include "Game.h"
#include <iostream>
#include "Obstacle.h"

Game::Game(sf::RenderWindow& existingWindow) : window(existingWindow)
{
    isGameOver = false;
    isMenu = true;
    score = 0;
    timeLeft = 60.f;

    window.setFramerateLimit(60);

    // Charger assets
    assets.load();

    // Texte Game Over
    gameOverText.setFont(assets.getFont("arial"));
    gameOverText.setString("GAME OVER\nAppuyez sur Entree pour quitter");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150, 250);

    // Score
    scoreText.setFont(assets.getFont("arial"));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(20, 20);

    // Backgrounds
    if (!menuTex.loadFromFile("assets/water2.jpg"))
        std::cerr << "Erreur chargement menu" << std::endl;
    menuSprite.setTexture(menuTex);

    if (!backTex.loadFromFile("assets/fish2.jpg"))
        std::cerr << "Erreur chargement background" << std::endl;
    backSprite.setTexture(backTex);

    // Player
    player = new Player(assets.getTexture("player"));

    // Musique
    if (music.openFromFile("assets/dragon-studio-underwater-ambience-376890.mp3"))
    {
        music.setLoop(true);
        music.play();
    }
}

void Game::run()

{
   
    while (window.isOpen())
    {
        update();
        render();
    }
}

void Game::update()
{
    sf::Event e;
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window.close();

        if (isMenu && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
        {
            isMenu = false;
            clock.restart();
            obstacleClock.restart();
        }

        if (isGameOver && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
        {
            window.close();
        }
    }

    if (isMenu || isGameOver)
    {
        clock.restart();
        return;
    }

    float dt = clock.restart().asSeconds();

    player->update();

    // Spawn obstacles
    if (obstacleClock.getElapsedTime().asSeconds() > 2.0f)
    {
        obstacles.push_back(new Obstacle());
        obstacleClock.restart();
    }

    // Update obstacles
    for (size_t i = 0; i < obstacles.size();)
    {
        obstacles[i]->update();

       /* if (player->getBounds().intersects(obstacles[i]->getBounds()))
        {
            isGameOver = true;
        }*/

        if (obstacles[i]->getBounds().left < -100)
        {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // Time
    timeLeft -= dt;
    if (timeLeft <= 0)
        isGameOver = true;

    // Score
    static float timer = 0;
    timer += dt;

    if (timer >= 1.0f)
    {
        score += 10;
        timer = 0;
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void Game::render()
{
    window.clear();

    if (isMenu)
    {
        window.draw(menuSprite);
    }
    else
    {
        window.draw(backSprite);

        for (auto obs : obstacles)
            obs->draw(window);

        if (player)
            player->draw(window);

        window.draw(scoreText);

        if (isGameOver)
            window.draw(gameOverText);
    }

    window.display();
}

Game::~Game()
{
    delete player;

    for (auto obs : obstacles)
        delete obs;

    obstacles.clear();
}