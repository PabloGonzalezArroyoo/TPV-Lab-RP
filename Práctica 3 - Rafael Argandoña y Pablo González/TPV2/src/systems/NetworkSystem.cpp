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

	cout << "Cual es tu nombre?\n>";
	cin >> name;

	do {
		cout << "\nEscoge tu rol\n  - CLIENTE\n  - HOST\n  - SALIR\n>";
		cin >> choice;

		if (choice == "HOST" || choice == "host" || choice == "h" || choice == "H") {
			hostName = name;
			done = initHost();
			correct = true;
		}// Todo host
		else if (choice == "CLIENTE" || choice == "cliente" || choice == "c" || choice == "C") {
			done = initClient();
			correct = true;
		}// Todo cliente
		else if (choice == "SALIR " || choice == "salir" || choice == "s" || choice == "S") {
			correct = true;
		}// Salir
	} while (!correct);

	return done;
}

bool NetworkSystem::initHost() {
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		cerr << "PUERTO NO VALIDO" << endl;
		return false;
	}
	cout << "El puerto disponible es: "  << ip.port << endl;
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		cerr << "NO HAY MASTER SOCKET" << endl;
		return false;
	}

	sockSet = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet, masterSocket);

	if (SDLNet_CheckSockets(sockSet, SDL_MAX_UINT32) > 0) {
		if (SDLNet_SocketReady(masterSocket)) {
			sock = SDLNet_TCP_Accept(masterSocket);
			cout << "SE CONECTO ALGUIEN" << endl;
		}
	}

	auto n = name.c_str();
	cout << n << endl;

	RequestConection rc;
	rc.id = _nw_REQUEST_CONNECTION;
	int i = 0;
	for (; i < name.size() && i < 10; i++) {
		rc.name[i] = name[i];
	}
	rc.name[i] = 0;

	//SDLNetUtils::serializedSend(rc, sock);

	SDLNet_TCP_Send(sock, name.c_str(), name.length() + 1);

	SDLNet_TCP_Recv(sock, buffer, 255);
	name = (string)buffer;

	cout << name << endl;

	host = true;
	connected = false;
	cout << "TODO BIEN, TODO CORRECTO" << endl;
	return true;
}

bool NetworkSystem::initClient() {
	int result = 0;

	cout << "\nIntroduce el host:\n>";
	cin >> hostName;
	cout << "\nIntroduce el puerto:\n>"; 
	cin >> port;

	auto h = hostName.c_str();
	auto a = SDLNet_ResolveHost(&ip, h, port);
	ip.port = port;

	if (a < 0) {
		cerr << "ERROR DE CONEXION AL HOST" << endl;
		return false;
	}

	sock = SDLNet_TCP_Open(&ip);
	if (!sock) {
		cerr << "NO SE HA CONSEGUIDO ESTABLECER LA CONEXION" << endl;
		return false;
	}
	else {
		cout << "!Me conecte al host " << ip.host << " en el puerto " << port << endl;
	}

	// ESPERAMOS POR CONFIRMACION DE CONEXION
	result = SDLNet_TCP_Recv(sock, buffer, 255);
	if (result < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	else if (result == 0) cout << "EL SERVIDOR CERRO LA CONEXION" << endl;
	else {
		hostName = buffer;
		cout << "EL SERVIDOR ACEPTO LA CONEXION. HOSTNAME: " << hostName << endl;
	}

	cout << "TU NOMBRE ES: " << name.c_str() << endl;
	SDLNet_TCP_Send(sock, name.c_str(), name.length() + 1);
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

void NetworkSystem::convertInfo(string& str) {
	int i = 0u;
	for (; i < str.size() && i < 255; i++) {
		buffer[i] = str[i];
	}
	buffer[i] = 0;
}

void NetworkSystem::revertInfo(string& str) {

}