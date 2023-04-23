#pragma once
#include "../ecs/System.h"
#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include "../components/TextComponent.h"
#include "../systems/NetworkSystem.h"

class RenderSystem : public System {
public:
	constexpr static sysId_type id = _sys_RENDER;

	~RenderSystem();
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const Message& m) override;
	
	// Inicializar el sistema, etc.
	virtual void initSystem() override;

	// Dibujar los objetos que toquen segun el estado
	virtual void update() override;

	// Cambia el texto del cliente
	void changeClientText(string newName);

private:
	// Creamos los textos necesarios segun el estado en el que nos encontremos
	void createTexts();
	// Inicializa un objeto texto con su textura y posicion
	void initializeText(string texture, int position);

	// Métodos de renderizado
	void renderGroup(grpId_type group, string key) const;
	void renderAsteroids();
	void renderTexts() const;
	void renderUI() const;

	// Variables de tiempo y estado
	NetworkSystem* nw;
	Texture* namesTxts[2];
	float startTime;
	STATE state;
};