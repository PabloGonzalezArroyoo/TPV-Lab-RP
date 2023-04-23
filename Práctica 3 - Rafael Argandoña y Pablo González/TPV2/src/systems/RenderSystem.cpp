#include "RenderSystem.h"
#include "../ecs/Manager.h"

RenderSystem::~RenderSystem() {
	for (Texture* txt : namesTxts) {
		if (txt != nullptr) delete namesTxts;
	}
}

// Recibir mensajes
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
		// Al iniciar un estado, guardarlo y crear textos correspondientes
		case _m_INIT_STATE:
			state = m._state_data.st;
			createTexts();
			break;
	}
}

// Inicializamos el sistema (solo empezamos el contador)
void RenderSystem::initSystem() {
	startTime = sdlutils().currRealTime();
	nw = nullptr;
}

void RenderSystem::update() {
	// Pintamos los grupos general y el de las balas
	renderGroup(_grp_GENERAL, FIGHTER);
	renderGroup(_grp_BULLETS, FIRETXT);
	renderGroup(_grp_MULTIPLAYER, FIGHTER);
	renderGroup(_grp_MULTIPLAYER_BULLETS, FIRETXT2);
	// Pintamos los asteroides
	renderAsteroids();
	// Si estamos en el estado de juego o de pausa pintamos las vidas del jugador
	if (state == PLAY_STATE || state == PAUSE_STATE) renderUI();
	// Pintamos los texto que haya en la escena
	renderTexts();
}

// Crear textos según el estado en el que se encuentra el sistema
void RenderSystem::createTexts(){
	switch (state) {
		// Main Menu
		case MAINMENU_STATE:
			initializeText(MM_ST, 1);
			initializeText(START_MESSAGE, 4);
		break;
		
		// Pausa
		case PAUSE_STATE:
			initializeText(PAUSE_ST, 1);
			initializeText(CONTINUE_MESSAGE, 4);
		break;
		
		// Victoria
		case WIN_STATE:
			initializeText(WIN_ST, 1);
			initializeText(WIN_MESSAGE, 2);
			initializeText(CONTINUE_MESSAGE, 4);
		break;

		// Derrota
		case GAMEOVER_STATE:
			initializeText(GAMEOVER_ST, 1);
			initializeText(GAME_OVER_MESSAGE, 2);
			initializeText(CONTINUE_MESSAGE, 4);
		break;

		//Multijugador
		case MULTI_PLAYER:
			nw = mngr->getSystem<NetworkSystem>();
			namesTxts[0] = new Texture(sdlutils().renderer(), nw->getMyName(), sdlutils().fonts().at(CHIMERA), SDL_Color());
			namesTxts[1] = new Texture(sdlutils().renderer(), nw->getOtherName(), sdlutils().fonts().at(CHIMERA), SDL_Color());
			break;
	}
}

// Inicializar textos según la textura recibida y un factor de posición
void RenderSystem::initializeText(string texture, int position) {
	// Añadir entidad y textura
	Entity* text = mngr->addEntity(_grp_TEXTS);
	Texture* txt = &sdlutils().msgs().at(texture);

	// Añadir componente de texto y transform
	mngr->addComponent<TextComponent>(text, txt);
	mngr->addComponent<Transform>(text, Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * position / 6 - txt->height() / 2),
		txt->width(), txt->height());
}

// Renderizar asteroides
void RenderSystem::renderAsteroids() {	
	// Incializar variables y coger asteroides
	auto asts = mngr->getEntities(_grp_ASTEROIDS);
	Transform* tr = nullptr;
	FramedImage* fi = nullptr;
	int frame = 0;

	// Pintar los asteroides
	for (int i = 0; i < asts.size(); i++) {
		// Coger componentes y nº de frames
		fi = mngr->getComponent<FramedImage>(asts[i]);
		tr = mngr->getComponent<Transform>(asts[i]);
		frame = fi->getCurrentFrame();

		// Renderizar la textura en el frame correspondiente
		fi->getImageTexture()->render(fi->getSrcRect(), tr->getRect()); 
		
		// Siguiendo el frame rate, actualizar frame a renderizar
		if (sdlutils().currRealTime() - startTime >= FRAME_RATE) fi->setCurrentFrame(frame + 1);
	}

	// Siguiendo el frame rate, actualizar el tiempo
	if (sdlutils().currRealTime() - startTime >= FRAME_RATE) startTime = sdlutils().currRealTime();
}

// Renderizar textos
void RenderSystem::renderTexts() const {
	// Pillamos los textos de la escena
	vector<Entity*> entities = mngr->getEntities(_grp_TEXTS); 
	Transform* tr = nullptr;
	// Los recorremos pintando su textura asociada
	for (int i = 0; i < entities.size(); i++) {
		tr = mngr->getComponent<Transform>(entities[i]);
		mngr->getComponent<TextComponent>(entities[i])->getTexture()->render(tr->getRect());
	}
}

// Renderizar UI
void RenderSystem::renderUI() const{
	// Pillamos el componente y la textura de la vida
	Health* h = mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER));
	Texture* text = &sdlutils().images().at(HEART);
	// Creamos una ventana para pintarlas
	SDL_Rect rect;
	rect.x = UPPER_LEFT_CORNER_X;
	rect.y = UPPER_LEFT_CORNER_Y;
	rect.w = text->width() / 4;
	rect.h = text->height() / 4;
	// Pintamos la textura tantas veces como vidas tenga el jugador desplazandonos en x
	for (int i = 0; i < h->getLifes(); i++) {
		rect.x = UPPER_LEFT_CORNER_X + i * (rect.w + 5);
		text->render(rect);
	}
}

// Renderizar un grupo
void RenderSystem::renderGroup(grpId_type group, string key) const {
	// Cogemos las entidades del grupo
	vector<Entity*> entities = mngr->getEntities(group);
	Transform* tr = nullptr;
	// Recorremos el grupo pintando la textura dada en la posicion del objeto
	for (int i = 0; i < entities.size(); i++) {
		tr = mngr->getComponent<Transform>(entities[i]);
		Texture* txt = &sdlutils().images().at(key);
		txt->render(tr->getRect(), tr->getRotation());
	}

	if (group == _grp_GENERAL && state == MULTI_PLAYER) {
		SDL_Rect r;
		r.w = namesTxts[0]->width(); r.h = namesTxts[0]->height();
		r.x = tr->getPosition().getX() + tr->getWidth()/2 - r.w / 2; r.y = tr->getPosition().getY() + tr->getHeight();
 		namesTxts[0]->render(r);
	}

	if (group == _grp_MULTIPLAYER && state == MULTI_PLAYER) {
		SDL_Rect r;
		r.w = namesTxts[1]->width(); r.h = namesTxts[1]->height();
		r.x = tr->getPosition().getX() + tr->getWidth() / 2 - r.w / 2; r.y = tr->getPosition().getY() + tr->getHeight();
		namesTxts[1]->render(r);
	}
}