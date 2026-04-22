
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
// =====================================================
// 🪟 WINDOW SETTINGS
// =====================================================
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS_LIMIT = 60;

// =====================================================
// 🎮 GAME GENERAL
// =====================================================
const float START_SPEED = 250.f;
const float SPEED_INCREMENT = 100.f;

const float START_SCORE = 0.f;
const float SCORE_RATE = 10.f;

const float MAX_LIFE = 100.f;
const float START_LIFE = 100.f;

const float MAX_TIME = 60.f;
const float EXTRA_TIME = 10.f;

// =====================================================
// 👤 PLAYER
// =====================================================
const float PLAYER_SPEED = 300.f;
const float PLAYER_SIZE = 100.f;

const float PLAYER_LIMIT_MARGIN = 0.f;

// =====================================================
// 🌊 OBSTACLES
// =====================================================
const float OBSTACLE_SPEED = 200.f;
const float OBSTACLE_SIZE = 60.f;

const int SPAWN_RATE_LEVEL_1 = 2;
const int SPAWN_RATE_LEVEL_2 = 5;

const int SPAWN_X = 1000;
const int SPAWN_Y_MIN = 50;
const int SPAWN_Y_MAX = 550;

// =====================================================
// 🎯 OBSTACLE TYPES PROBABILITY
// =====================================================
const int PROB_BONUS = 0;
const int PROB_DAMAGE = 1;
const int PROB_SPEED = 2;
const int PROB_SCORE = 3;

// =====================================================
// 🎨 MENU
// =====================================================
const int MENU_TITLE_SIZE = 50;
const int MENU_TEXT_SIZE = 30;

const int MENU_PLAY_Y = 250;
const int MENU_ABOUT_Y = 320;
const int MENU_QUIT_Y = 390;

// =====================================================
// 🖼️ ASSETS PATHS
// =====================================================
const char PLAYER_TEXTURE[] = "assets/diver.png";
const char OBSTACLE_TEXTURE[] = "assets/fish1.jpg";

const char MENU_BACKGROUND[] = "assets/menu.png";
const char LEVEL1_BACKGROUND[] = "assets/water2.jpg";
const char LEVEL2_BACKGROUND[] = "assets/background nocturne.png";
const char FONT_PATH[] = "assets/Fonts/arial.ttf";


// =====================================================
// 🎵 AUDIO
// =====================================================
// 🎵 MUSIC (background)
// 🎵 MUSIC (background)
const std::string MUSIC_PATH = "assets/make-a-music-game-in-sunknetcity--with-ambinece-for-kids-_042026.mp3";

// 🔊 SOUND EFFECT
const std::string WIN_SOUND_PATH = "assets/winsongs.mp3";
const std::string GAMEOVER_SOUND_PATH = "assets/game_over.mp3";

#endif