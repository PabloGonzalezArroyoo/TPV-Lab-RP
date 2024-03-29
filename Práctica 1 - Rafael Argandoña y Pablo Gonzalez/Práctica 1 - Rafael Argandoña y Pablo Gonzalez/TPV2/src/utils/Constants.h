#pragma once
#include "Vector2D.h"
#include "../utils/chekML.h"
#include <string>

using namespace std;

// PANTALLA
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int UPPER_LEFT_CORNER_X = 10;
const int UPPER_LEFT_CORNER_Y = 10;

// RECURSOS
// Fuentes
const string ARIAL = "ARIAL";
const string CAPTURE = "CAPTURE";
const string CHIMERA = "CHIMERA";
// Texturas
const string ASTEROID_A = "asteroidA";
const string ASTEROID_B = "asteroidB";
const string FIGHTER = "fighter";
const string FIGHTER2 = "fighter2";
const string FIRETXT = "fire";
const string HEART = "heart";
// Sonidos
const string EXPLOSION = "explosion";
const string FIRESFX = "fire";
const string OOF = "oof";
const string SELECT = "select";
const string THRUST = "thrust";
// Musica
const string GALAXY = "galaxy";
// Messages
const string MM_MESSAGE = "MM_MSG";
const string PAUSE_MESSAGE = "PAUSE_MSG";
const string GAME_OVER_MESSAGE = "GAMEOVER_MSG";

// PLAYER
const int MAX_LIFES = 3;     
const int PLAYER_WIDTH = 48;
const int PLAYER_HEIGHT = 48;
const Vector2D PLAYER_INITIAL_POS = Vector2D(WIN_WIDTH / 2 - PLAYER_WIDTH / 2, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2);

// ASTEROIDS
const int ASTEROIDS_WIDTH = 34;
const int ASTEROIDS_HEIGHT = 40;
const float ASTEROIDS_DIMENSIONS = 20.0f;
const int ASTEROIDS_FRAME_WIDTH = 85;
const int ASTEROIDS_FRAME_HEIGHT = 100;
const int ASTEROIDS_ROWS = 5;
const int ASTEROIDS_COLS = 6;
const int LIMIT_ASTEROIDS = 30;
const int AST_FRAME_NUMBER = ASTEROIDS_COLS * ASTEROIDS_ROWS;
const int FRAME_RATE = 50;
const int AST_FREQUENCY = 5000;

// BALA
const int BULLET_WIDTH = 5;
const int BULLET_HEIGTH = 20;