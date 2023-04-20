#include "NetworkSystem.h"

NetworkSystem::NetworkSystem() : host(false), sock(), sockSet(), port(1), connected(false), ip() { }

NetworkSystem::~NetworkSystem() {
	SDLNet_TCP_Close(sock);
	if (masterSocket) SDLNet_TCP_Close(masterSocket);
}

void NetworkSystem::receive(const Message& m) {

}

void NetworkSystem::initSystem() {
	connect();
}

bool NetworkSystem::connect() {
	string choice;
	bool done = false, correct = false;

	cout << "Cual es tu nombre?: ";
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

bool NetworkSystem::initHost() {
	/*Uint16 p;
	cout << "Introduzca el numero de puerto a usar: ";

	if (!(cin >> p)) { cerr << "Puerto no valido" << endl; return false; }
	if (!initConnection(p)) return false;

	hostName = name;
	host = true;
	connected = false;
	return true;*/
	
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		cerr << "PUERTO NO VALIDO" << endl;
		return false;
	}

	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		cerr << "NO HAY MASTER SOCKET" << endl;
		return false;
	}

	sockSet = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet, masterSocket);

	hostName = name;
	host = true;
	connected = false;
	initConnection(port);
	cout << "TODO BIEN, TODO CORRECTO" << endl;
	return true;
}

bool NetworkSystem::initClient() {
	int result = 0;
	//buffer[256];

	cout << "Introduce el host: " << endl;
	if (!(cin >> hostName)) {
		cerr << "Invalid host" << std::endl;
		return false;
	}
	auto h = hostName.c_str();
	auto a = SDLNet_ResolveHost(&ip, h, port);
	cout << a << endl;
	if (a < 0) {
		cerr << "ERROR DE CONEXION AL HOST" << endl;
		return false;
	}

	sock = SDLNet_TCP_Open(&ip);
	if (!sock) {
		cerr << "NO SE HA CONSEGUIDO ESTABLECER LA CONEXION" << endl;
		return false;
	}

	// ESPERAMOS POR CONFIRMACION DE CONEXION
	result = SDLNet_TCP_Recv(sock, buffer, 1);
	if (result < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	else if (result == 0) cout << "EL SERVIDOR CERRO LA CONEXION" << endl;

	else {
		if (buffer[0] == 0) {
			cout << "CONECTAO" << endl;
			connected = true;
		}
		else {
			cout << "CONEXION NO ACEPTADA" << endl;
			connected = false;
		}
	}
}

bool NetworkSystem::initConnection(const Uint16& port_) {

	if (host) {
		if (SDLNet_SocketReady(masterSocket)) {
			sock = SDLNet_TCP_Accept(masterSocket);
			SDLNet_TCP_AddSocket(sockSet, sock);
		}
	}
	return true;
}

void NetworkSystem::disconnect() {
	if (connected) {
		SDLNet_FreeSocketSet(sockSet);
		SDLNet_TCP_Close(masterSocket);
	}
}