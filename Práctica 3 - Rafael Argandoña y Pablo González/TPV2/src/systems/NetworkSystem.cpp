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
	cout << "TODO BIEN, TODO CORRECTO" << endl;
	return true;
}

bool NetworkSystem::initClient() {
	//Uint16 p;
	//string host_;

	//cout << "Introduzca el host y el puerto: " << endl;
	//if (!(cin >> host_ >> p)) { cout << "Host/Puerto no valido" << endl; return false; }
	//if (!SDLNet_ResolveHost(&otherAddr, host_.c_str(), p) < 0) {
	//	SDLNetUtils::print_SDLNet_error(); return false;
	//}

	//host = false;
	//initConnection(0);

	////Lanzar mensaje de Peticion de conexion

	//pack->address = otherAddr;
	////SDLNetUtils::serializedSend();

	//if (SDLNet_CheckSockets(sockSet, 3000) > 0) {
	//	if (SDLNet_SocketReady(sock)) {
	//		/*SDLNetUtils::deserializedReceive();
	//		if (MI SOLICITUD SE ACEPTO) {
	//			DESERIALIZO EL MENSAJE
	//			host = false;
	//			connected = true;
	//		}*/

	//	}
	//}

	//if (!connected) {
	//	cout << "No se pudo conectar con el otro jugador" << endl;
	//	return false;
	//}

	//return true;
	int result = 0;
	//buffer[256];

	if (SDLNet_ResolveHost(&ip, hostName.c_str(), port) < 0) {
		cerr << "ERROR DE CONEXION AL HOST" << endl;
		return false;
	}

	sock = SDLNet_TCP_Open(&ip);
	if (!sock) {
		cerr << "NO SE HA CONSEGUIDO ESTABLECER LA CONEXION" << endl;
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