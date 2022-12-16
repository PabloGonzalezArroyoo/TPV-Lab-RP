#include "PlayState.h"
#include "Game.h"
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

	//Añadimos el mapa de bloques
	ifstream in;
	in.open(levels[currentLevel] + ".dat");
	if (!in.is_open()) throw FileNotFoundError("Couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
	objects.push_back(new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGHT / 2 - WALL_WIDTH, game->getTexture(Blocks), in));
	in.close();

	itAux = objects.begin();
	blocksmap = static_cast<BlocksMap*> (*itAux);
	
	//Añadimos las paredes

	objects.push_back(new Wall(Vector2D(0, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGHT - WALL_WIDTH, game->getTexture(SideWall), Vector2D(1, 0)));
	objects.push_back(new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGHT - WALL_WIDTH, game->getTexture(SideWall), Vector2D(-1, 0)));
	objects.push_back(new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_WIDTH, game->getTexture(TopWall), Vector2D(0, 1)));
	for (int i = 0; i < 3; i++) {
		itAux++;
		walls[i] = static_cast<Wall*>(*itAux);
	}

	//Añadimos la plataforma
	objects.push_back(new Paddle(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGHT - 30), 100, 10, game->getTexture(PaddleTxt), Vector2D(0, 0)));
	itAux++;
	paddle = static_cast<Paddle*> (*itAux);

	//Añadimos la pelota
	objects.push_back(new Ball(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGHT - 50), 15, 15, game->getTexture(BallTxt), Vector2D(1, -1), this));
	itAux++;
	ball = static_cast<Ball*> (*itAux);

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
	for (int i = 0; i < numRewards; ++i) {
		rAux = new Reward(); rAux->loadFromFile(in, game->getTexture(Rewards));
		rAux->setGameDepend(this); objects.push_back(rAux);
	}
	itFirstReward = objects.end();
}

// Destructora
PlayState::~PlayState() {
	for (GameObject* myOb : objects) delete(myOb);
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

		/*for (list<GameObject*>::iterator it = next(reward); it != objects.end(); (it++)++) {
			Reward* myR = static_cast<Reward*> (*it);
			myR->changeIterator();
		}*/

		for (int i = 0; i < objToDestroy.size(); i++) {
			objects.erase(objToDestroy[i]);
		}
		objToDestroy.clear();

		checkNextLevel(false);
	}
	else isPaused = false;

	if (win) game->end(win);
	if (gameOver) game->end(gameOver);
}

// Maneja los eventos de pausa y movimiento de la pala
void PlayState::handleEvent(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_ESCAPE && !isPaused) {	// Si el jugador ha pulsado ESCAPE, se lanza el estado de pausa
		isPaused = true;
		game->pause();
	}
	else paddle->handleEvent(event);						// Si el evento es de otro tipo llamamos a la pala (por si son sus teclas de mov)

}

// Comprobar colisiones del Ball
bool PlayState::collidesBall(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - DeadLine
	if (rectBall.y >= WIN_HEIGHT - 10) { checkLife(); return true; }

	// Ball - Blocksmap
	if (rectBall.y <= WIN_HEIGHT / 2) {
		if (blocksmap->collides(rectBall, colV)) {
			//createReward(blocksmap->getDestroyedBlock());
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
	case 'R': ++life; lifeLeft(); break;					// +1 de vida
	case 'E': paddle->changeDimensions(true); break;		// Alargar pala
	case 'S': paddle->changeDimensions(false); break;		// Acortar pala
	}
}

void PlayState::deleteReward(list<GameObject*>::iterator reward) {									
	objToDestroy.push_back(reward);									// Borramos de la lista la reward
	//delete(*reward);												// Eliminamos el objeto en la memoria
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

// Gestionar vida: quitar un punto de vida y resetear posiciones de entidades
void PlayState::checkLife() {
	--life;											// Decrementamos la vida							
	if (life <= 0) gameOver = true;					// Si no quedan vidas, fin de la partida
	else reloadItems();								// Si quedan, resetear la posición inicial la pala y la pelota
	lifeLeft();										// Mostrar info en la consola
}

// Muestra en consola la vida actual
void PlayState::lifeLeft() {
	// Borrar consola según SO
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	// Escribir en consola
	cout << "VIDAS RESTANTES: " << life << endl;
}

// Vuelve los items a su estado inicial (p.ej: cuando se pierde una vida)
void PlayState::reloadItems() {

	// Borra los rewards presentes en partida
	for (list<GameObject*>::iterator it = itFirstReward; it != objects.end(); it++) {
		objToDestroy.push_back(it);
	}

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
		myOb->saveToFile(out); 
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