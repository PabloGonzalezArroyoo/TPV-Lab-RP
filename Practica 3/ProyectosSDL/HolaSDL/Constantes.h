// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

using namespace std;
typedef unsigned int uint;

// Tamaño de ventana
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;

// Texturas
const uint NUM_TEXTURES = 18;

// Framerate
const uint FRAMERATE = 5;

// Propiedades del jugador
const uint NUM_LEVELS = 3;
const uint NUM_LIFES = 3;

// Escenario
const uint WALL_WIDTH = 15;

// Botones
const uint BUTTON_WIDTH = 300;
const uint BUTTON_HEIGHT = 75;

// Ball
const uint BALL_WIDTH = 15, BALL_HEIGHT = 15;
const double BALL_X = WIN_WIDTH / 2 - WALL_WIDTH;
const double BALL_Y = WIN_HEIGHT - 50;

// Lifes
const uint LIFES_GAP = 20;
const double LIFE_HEIGHT = WIN_HEIGHT - 20;

// Paddle
const uint PADDLE_AREA = WIN_HEIGHT - 40;
const uint PADDLE_WIDTH = 100, PADDLE_HEIGHT = 10;
const double PADDLE_X = WIN_WIDTH / 2 - WALL_WIDTH * 2;
const double PADDLE_Y = WIN_HEIGHT - 30;

// Reward
const uint REWARD_WIDTH = 35, REWARD_HEIGHT = 20;