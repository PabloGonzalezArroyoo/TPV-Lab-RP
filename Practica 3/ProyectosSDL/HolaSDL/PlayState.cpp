#include "PlayState.h"
#include "Game.h"
#include "EndState.h"
#include "PauseState.h"
#include <iostream>
#include <fstream>

// Constructora vacía
PlayState::PlayState() {
	game = nullptr; blocksmap = nullptr; paddle = nullptr; ball = nullptr;
	life = 0; currentLevel = 0;
	gameOver = false; win = false; isPaused = false;
}

// Constructora
PlayState::PlayState(Game* g) : GameState(g) {
	list<GameObject*>::iterator itAux;

	// Poner el nivel actual a 0 y las vidas a su constante
	currentLevel = 0; life = NUM_LIFES;
	gameOver = false; win = false; isPaused = false;

	// Añadimos el mapa de bloques
	ifstream in;
	in.open(levels[currentLevel] + ".dat");
	if (!in.is_open()) throw FileNotFoundError("Couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
	objects.push_back(new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGHT / 2 - WALL_WIDTH, game->getTexture(Blocks), in));
	in.close();

	itAux = objects.begin();
	blocksmap = static_cast<BlocksMap*> (*itAux);
	
	// Añadimos las paredes
	objects.push_back(new Wall(Vector2D(0, WALL_WIDTH), WALL_WIDTH, WIN_HEIGHT - WALL_WIDTH, game->getTexture(SideWall), Vector2D(1, 0)));
	objects.push_back(new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, WALL_WIDTH), WALL_WIDTH, WIN_HEIGHT - WALL_WIDTH, game->getTexture(SideWall), Vector2D(-1, 0)));
	objects.push_back(new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_WIDTH, game->getTexture(TopWall), Vector2D(0, 1)));
	for (int i = 0; i < 3; i++) {
		itAux++;
		walls[i] = static_cast<Wall*>(*itAux);
	}

	// Añadimos las imagenes de las vidas
	for (int i = 0; i < life; i++) {
		objects.push_back(new Image(game->getTexture(BallTxt), Vector2D(LIFES_GAP * i, LIFE_HEIGHT), BALL_WIDTH, BALL_HEIGHT));
		lifes.push(prev(objects.end()));
		itAux++;
	}

	// Añadimos la plataforma
	objects.push_back(new Paddle(Vector2D(PADDLE_X, PADDLE_Y), PADDLE_WIDTH, PADDLE_HEIGHT, game->getTexture(PaddleTxt), Vector2D(0, 0)));
	itAux++;
	paddle = static_cast<Paddle*> (*itAux);

	// Añadimos la pelota
	objects.push_back(new Ball(Vector2D(BALL_X, BALL_Y), BALL_WIDTH, BALL_HEIGHT, game->getTexture(BallTxt), Vector2D(1, -1), this));
	itAux++;
	ball = static_cast<Ball*> (*itAux);

	// Asignar iterador de rewards
	itFirstReward = objects.end();
}

PlayState::PlayState(Game* g, ifstream& in) : GameState(g) {
	// Booleanos de control
	gameOver = false; win = false; isPaused = false;

	// Leer nivel actual y vida
	in >> currentLevel;
	in >> life;
	
	// Punteros auxiliares
	BlocksMap* bmAux; Wall* wallAux; Paddle* pAux; Ball* bAux; Reward* rAux;

	// Leer blocksmap
	bmAux = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGHT / 2 - WALL_WIDTH, game->getTexture(Blocks), in);
	objects.push_back(bmAux);
	blocksmap = bmAux;

	// Leer las paredes
	wallAux = new Wall(); wallAux->loadFromFile(in, game->getTexture(SideWall)); objects.push_back(wallAux); walls[0] = wallAux;
	wallAux = new Wall(); wallAux->loadFromFile(in, game->getTexture(SideWall)); objects.push_back(wallAux); walls[1] = wallAux;
	wallAux = new Wall(); wallAux->loadFromFile(in, game->getTexture(TopWall)); objects.push_back(wallAux); walls[2] = wallAux;

	// Añadimos las imagenes de las vidas
	for (int i = 0; i < life; i++) {
		objects.push_back(new Image(game->getTexture(BallTxt), Vector2D(LIFES_GAP * i, LIFE_HEIGHT), BALL_WIDTH, BALL_HEIGHT));
		lifes.push(prev(objects.end()));
	}

	// Leer la pala
	pAux = new Paddle(); pAux->loadFromFile(in, game->getTexture(PaddleTxt)); objects.push_back(pAux);
	paddle = pAux;

	// Leer la bola y setear su iterador
	bAux = new Ball(); bAux->loadFromFile(in, game->getTexture(BallTxt));
	bAux->setGameDepend(this); objects.push_back(bAux);
	ball = bAux;

	// Comprobar si hay rewards y leerlas en caso afirmativo
	int numRewards = 0;
	in >> numRewards;
	if (numRewards == 0) itFirstReward = objects.end();

	for (int i = 0; i < numRewards; ++i) {
		rAux = new Reward(); rAux->loadFromFile(in, game->getTexture(Rewards));
		rAux->setGameDepend(this); objects.push_back(rAux);
		if (i == 0) itFirstReward = prev(objects.end());
	}
}

// Renderizado
void PlayState::render() {
	// Renderizado de los objetos del juego
	for (list<GameObject*>::iterator it = objects.begin(); it != objects.end(); it++)
		if ((*it) != nullptr) (*it)->render();
}

// Actualizar entidades
void PlayState::update() {
	if (!isPaused) {
		ball->update();
		// Actualización de las rewards si existen
		for (list<GameObject*>::iterator it = itFirstReward; it != objects.end(); it++) {
			(*it)->update();
		}

		// Recorremos la lista de objetos a destruir
		for (int i = 0; i < objToDestroy.size(); i++) {
			GameObject* objTD = *objToDestroy[i];				// Nos guardamos a donde apunta el iterador
			objects.erase(objToDestroy[i]);						// Retiramos el objeto de la lista principal de objetos
			delete(objTD);										// Borramos la memoria del objeto, una vez ya este eliminado de la lista
		}
		objToDestroy.clear();									// Limpiamos la lista de objetos a destruir, para llenarla si es necesario en el siguiente update

		// Comprobar si se debe cambiar de nivel (false -> no es una llamada por parte de una reward)
		checkNextLevel(false);
	}
	else isPaused = false;

	// Pantalla de victoria o fin del juego
	if (win) game->getStateMachine()->changeState(new EndState(game, true));
	else if (gameOver) game->getStateMachine()->changeState(new EndState(game, false));
}

// Maneja los eventos de pausa y movimiento de la pala
void PlayState::handleEvent(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_ESCAPE && !isPaused) {	// Si el jugador ha pulsado ESCAPE, se lanza el estado de pausa
		isPaused = true;
		game->getStateMachine()->pushState(new PauseState(game));
	}
	else paddle->handleEvent(event);						// Si el evento es de otro tipo llamamos a la pala (por si son sus teclas de mov)
}

// Comprobar colisiones del Ball
bool PlayState::collidesBall(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - DeadLine
	if (rectBall.y >= WIN_HEIGHT - 10) {
		removeLife(); 
		return true; 
	}

	// Ball - Blocksmap
	if (rectBall.y <= WIN_HEIGHT / 2) {
		if (blocksmap->collides(rectBall, colV)) {
			createReward(blocksmap->getDestroyedBlock());
			return true;
		}
	}

	// Ball - Walls
	for (int i = 0; i < 3; ++i) {
		if (walls[i]->collides(rectBall, colV)) return true;
	}

	// Ball - Paddle
	if (rectBall.y > WIN_HEIGHT - 50 && ball->getVelocity().getY() > 0) {
		if (paddle->collides(rectBall, colV)) return true;
	}

	return false;
}

// Comprobar colisiones del Reward
bool PlayState::collidesReward(SDL_Rect rectReward) {
	//Si llegas abajo del todo o colisionas con la pala
	if (rectReward.y >= WIN_HEIGHT || SDL_HasIntersection(&rectReward, &paddle->getRect())) return true;

	return false;														// Negar colisión
}

// Crear reward en base a posibilidades
void PlayState::createReward(Vector2D rPos) {
	// Número aleatorio en un rango
	int random = 0 + (rand() % 40);
	random %= 8;

	// Asignar tipo
	char type = 'x';
	switch (random) {
		case 0: type = 'L'; break;
		case 1: type = 'R'; break;
		case 2: type = 'E'; break;
		case 3: type = 'S'; break;
	}

	// Si no es de tipo vacío, instanciarlo y añadirlo a la lista
	if (type != 'x') {
		objects.push_back(new Reward(rPos, game->getTexture(Rewards), Vector2D(0, 1), type, this));
		Reward* myRw = static_cast<Reward*> (*prev(objects.end()));
		myRw->setIterator(prev(objects.end()));
		if (itFirstReward == objects.end()) itFirstReward = prev(objects.end());
	}
}

// Llama al comportamiento correspondiente al reward recibido
void PlayState::rewardBehaviour(char type) {
	switch (type) {
	case 'L': checkNextLevel(true); break;					// Cambio de nivel
	case 'R': addLife(); break;								// +1 de vida
	case 'E': paddle->changeDimensions(true); break;		// Alargar pala
	case 'S': paddle->changeDimensions(false); break;		// Acortar pala
	}
}

// Añade la reward a la lisa de objetos para borrar
void PlayState::deleteReward(list<GameObject*>::iterator reward) {
	if (reward == itFirstReward) itFirstReward++;					// Si es la primera reward, actualizar el iterador para evitar errores
	objToDestroy.push_back(reward);									// Borramos de la lista la reward
}

// Comprobar si se ha pasado de nivel
void PlayState::checkNextLevel(bool rewardAct) {
	BlocksMap* myBm = dynamic_cast<BlocksMap*> (*(objects.begin()));

	if (myBm->getBlocks() == 0 || rewardAct) {												// Si no hay bloques
		++currentLevel;																		// Actualizamos el nivel en el que estamos

		if (currentLevel >= NUM_LEVELS) win = true;											// Si es el último nivel el jugador ha ganado
		else {																				// Si no es el último nivel
			reloadItems();																	// Volver los items a su posición inicial
			ifstream in;
			in.open(levels[currentLevel] + ".dat");
			if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
			myBm = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGHT / 2 - WALL_WIDTH, game->getTexture(Blocks), in); // Creamos el nuevo mapa (el siguiente)
			in.close();
			BlocksMap* oldBM = dynamic_cast<BlocksMap*> (*objects.begin());
			objects.pop_front();
			delete(oldBM);																	// Eliminamos el mapa que acabamos de superar
			objects.push_front(myBm);
			blocksmap = myBm;
			SDL_Delay(1500);																// Al cambiar de nivel tardamos en actualizar la pantalla
		}
	}
}

// Añade una vida al jugador y al HUD
void PlayState::addLife() {
	// Crear la nueva imagen del HUD, insertándola en la lista de obejtos y en el stack
	auto it = objects.insert(lifes.top(), new Image(game->getTexture(BallTxt), Vector2D(LIFES_GAP * life, LIFE_HEIGHT), BALL_WIDTH, BALL_HEIGHT));
	lifes.push(it);
	// Añadir vida
	++life;
}

// Quitar un punto de vida y resetear posiciones de entidades, comprobando si se pierde o no el nivel
void PlayState::removeLife() {
	--life;											// Decrementamos la vida
	objToDestroy.push_back(lifes.top());
	lifes.pop();
	if (life <= 0) gameOver = true;					// Si no quedan vidas, fin de la partida
	else reloadItems();								// Si quedan, resetear la posición inicial la pala y la pelota
}

// Vuelve los items a su estado inicial (p.ej: cuando se pierde una vida)
void PlayState::reloadItems() {

	// Borra los rewards presentes en partida
	for (list<GameObject*>::iterator it = itFirstReward; it != objects.end(); it++) {
		objToDestroy.push_back(it);
	}

	itFirstReward = objects.end();

	// Poner la bola y la pala en las posiciones y velocidades inciales
	ball->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGHT - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
	paddle->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGHT - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del juego
}

void PlayState::saveToFile(ofstream& out) {
	// Guardar nivel actual y vida
	out << currentLevel << " " << life << endl;

	// Guardar objetos de la lista de objetos
	for (list<GameObject*>::iterator it = objects.begin(); it != itFirstReward; it++) {
		ArkanoidObject* myOb = dynamic_cast<ArkanoidObject*> (*it);
		if (myOb != nullptr) myOb->saveToFile(out); 
		out << endl;
	}

	// Guardar los rewards en caso de haber
	if (itFirstReward != objects.end())
	{
		out << (objects.size() - 6) << endl;
		for (list<GameObject*>::iterator it = itFirstReward; it != objects.end(); it++) {
			ArkanoidObject* myOb = dynamic_cast<ArkanoidObject*> (*it);
			myOb->saveToFile(out); 
			out << endl;
		}
	}
}