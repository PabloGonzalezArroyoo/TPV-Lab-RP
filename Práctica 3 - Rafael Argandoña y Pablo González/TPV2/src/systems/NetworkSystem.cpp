#include "NetworkSystem.h"

NetworkSystem::NetworkSystem() : host(false), sock(), pack(), sockSet(), port(), connected(false), otherAddr() { }

void NetworkSystem::receive(const Message& m) {

}

void NetworkSystem::update() {

}

bool NetworkSystem::connect() {
	string choice;
	bool done = false, correct = false;

	cout << "¿Cual es tu nombre?: ";
	cin >> name;

	do {
		cout << "Escoge tu rol\n  - CLIENTE\n  - HOST\n  - SALIR\n>";
		cin >> choice;

		if (choice == "HOST" || choice == "host") {
			done = initHost();
			correct = true;
		}// Todo host
		else if (choice == "CLIENTE" || choice == "cliente") {
			done = initClient();
			correct = true;
		}// Todo cliente
		else if (choice == "SALIR " || choice == "salir") {
			correct = true;
		}// Salir
	} while (!correct);

	return done;
}

void NetworkSystem::disconnect() {

}

bool NetworkSystem::initHost() {
	Uint16 p;
	cout << "Introduzca el numero de puerto a usar: ";

	if (!(cin >> p)) { cerr << "Puerto no valido" << endl; return false; }
	if (!initConnection(p)) return false;

	hostName = name;
	host = true;
	connected = false;
	return true;
}

bool NetworkSystem::initClient() {
	Uint16 p;
	string host_;

	cout << "Introduzca el host y el puerto: " << endl;
	if (!(cin >> host_ >> p)) { cout << "Host/Puerto no valido" << endl; return false; }
	if (!SDLNet_ResolveHost(&otherAddr, host_.c_str(), p) < 0) {
		SDLNetUtils::print_SDLNet_error(); return false;
	}

	host = false;
	initConnection(0);

	//Lanzar mensaje de Peticion de conexion

	pack->address = otherAddr;
	//SDLNetUtils::serializedSend();

	if (SDLNet_CheckSockets(sockSet, 3000) > 0) {
		if (SDLNet_SocketReady(sock)) {
			/*SDLNetUtils::deserializedReceive();
			if (MI SOLICITUD SE ACEPTO) {
				DESERIALIZO EL MENSAJE
				host = false;
				connected = true;
			}*/

		}
	}

	if (!connected) {
		cout << "No se pudo conectar con el otro jugador" << endl;
		return false;
	}

	return true;
}

bool NetworkSystem::initConnection(const Uint16& port_) {
	sock = SDLNet_UDP_Open(port_);
	sockSet = SDLNet_AllocSocketSet(1);
	if (!sock || !sockSet) { SDLNetUtils::print_SDLNet_error(); return false; }

	SDLNet_UDP_AddSocket(sockSet, sock);
	pack = SDLNet_AllocPacket(512);

	if (!pack) { SDLNetUtils::print_SDLNet_error(); return false; }

	port = SDLNetUtils::getSocketPort(sock);
	return true;
}

void NetworkSystem::disconnect() {
	if (connected) {
		// LANZAS EL MENSAJE DE DESCONECTAR
	}
}