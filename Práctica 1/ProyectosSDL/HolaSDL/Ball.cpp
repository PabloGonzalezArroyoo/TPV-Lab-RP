#include "Ball.h"

Ball::Ball(Vector2D v, Vector2D velocity, uint width, uint height, Texture* txt) {
	pos = v; vel = velocity; w = width; h = height; texture = txt;
}

Ball::~Ball() {
	pos = vel = Vector2D();
	w = h = 0;
	delete(texture);
}

void Ball::render() {

}

void Ball::update() {

}

void Ball::collision() {

}