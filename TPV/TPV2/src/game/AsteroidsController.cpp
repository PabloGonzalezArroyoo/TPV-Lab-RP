#include "AsteroidsController.h"
#include "../sdlutils/SDLUtils.h"

AsteroidsController::AsteroidsController(Manager* _mng) : mng(_mng), numAst(0) { }

// TO-DO
void AsteroidsController::createAsteroids(int n) {
	for (int i = 0; i < n; i++) {
		Entity* asteroid = mng->addEntity(_grp_ASTEROIDS);
		asteroid->addComponent<Transform>();

		// Tipo B
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			// asteroid->addComponent<FramedImage>()
			asteroid->addComponent<Follow>();
		}
		// Tipo A
		else {
			// asteroid->addComponent<FramedImage>();
		}
		
	}
}

void AsteroidsController::addAsteroidsFrequently() {

}

void AsteroidsController::destroyAllAsteroids() {

}

void AsteroidsController::OnCollision(Entity* a) {

}

Vector2D AsteroidsController::randomPos() {
	int x = SDLUtils::instance()->rand().nextInt(0, WIN_WIDTH);
	int y = SDLUtils::instance()->rand().nextInt(0, WIN_HEIGHT);
	
	return Vector2D(x, y);
}