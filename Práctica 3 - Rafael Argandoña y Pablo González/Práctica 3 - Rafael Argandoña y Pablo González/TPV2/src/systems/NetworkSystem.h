#pragma once
#include "../ecs/System.h"
#include "../game/NetworkMessages.h"
#include "../components/Transform.h"

class NetworkSystem : public System{
private:
	// Booleano para saber el rol del ordenador
	bool host;

	// Ip y puerto del host
	IPaddress ip;
	Uint16 port;

	// Lista de sockets
	TCPsocket masterSocket;
	TCPsocket sock;
	SDLNet_SocketSet sockSet;

	// Booleanos de control
	bool connected;
	bool newBullet;

	// Buffer donde se guarda la información enviada/recibida
	char buffer[256];
	int prevNBullets, newNBullets;

	// Punteros a los transform de ambas entidades
	Transform* tr;
	Transform* gtr;

	// Nombres de los jugadores
	string name;
	string hostName;

	// Metodos para inicializar el ordenador segun el rol
	bool initHost();
	bool initClient();
	void showHostMessage();

	// Convertir el buffer en un string
	string revertInfo();

	// Enviar mensaje
	void sendMessage();

	// Decodificar inforamción
	void decode(string str);
	void decodeMessage(string line);

public:
	static constexpr sysId id = _sys_NETWORK_;

	// Constructora y destructora
	NetworkSystem();
	~NetworkSystem();

	// Metodos virtuales de todo sistema
	void receive(const Message& m) override;
	void initSystem() override;
	void update() override;

	// Metodos para manejar la conexion y desconexion
	bool connect();
	void disconnect();

	// Comprobadores
	inline bool isConnected() { return connected; }
	inline bool isHost() { return host; }

	// Getters
	inline Uint16 getPort() { return port; }
	inline string getMyName() { 
		if (host) return hostName;
		else return name;
	}
	inline string getOtherName() {
		if (host) return name;
		else return hostName;
	}
};