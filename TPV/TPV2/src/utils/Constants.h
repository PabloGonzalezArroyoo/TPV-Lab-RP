#pragma once
#include "Vector2D.h"

// PANTALLA
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int UPPER_LEFT_CORNER_X = 10;
const int UPPER_LEFT_CORNER_Y = 10;

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
// BALA
const int BULLET_WIDTH = 5;
const int BULLET_HEIGTH = 20;