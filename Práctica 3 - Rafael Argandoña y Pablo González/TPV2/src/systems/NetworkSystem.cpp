#include "NetworkSystem.h"
#include "../ecs/Manager.h"

NetworkSystem::NetworkSystem() : host(false), sock(), sockSet(), port(1), connected(false), ip() { }

NetworkSystem::~NetworkSystem() {
	SDLNet_TCP_Close(sock);
	if (masterSocket) SDLNet_TCP_Close(masterSocket);
}

void NetworkSystem::receive(const Message& m) {
	// RECIBE TODOS LOS MENSAJES QUE IMPORTEN AL OTRO PORTATIL (MOV, ROT, DISPARO)
	string inf;

	switch (m.id)
	{
		case _m_CREATE_BULLET:
			inf = "b";
			SDLNet_TCP_Send(sock, inf.c_str(), inf.size() + 1);
		break;

		case _m_INIT_STATE:
			tr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
			gtr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_GHOST_FIGHTER));
		break;
	}
}

void NetworkSystem::initSystem() {
	connect();
}

void NetworkSystem::update() {
	if (SDLNet_CheckSockets(sockSet, 0) > 0) {
		if (sock != nullptr && SDLNet_SocketReady(sock)) {
			if (SDLNet_TCP_Recv(sock, buffer, 255) > 0) {
				decode(revertInfo(), ' ');
			}
		}
	}

	// MANDO MI POSICION;
	sendTransform();

}

void NetworkSystem::sendTransform() {
	string info = "m ";
	info += to_string(tr->getPosition().getX());
	info += " ";
	info += to_string(tr->getPosition().getY());
	info += " ";
	info += to_string(tr->getRotation());

	SDLNet_TCP_Send(sock, info.c_str(), info.size() + 1);
}

void NetworkSystem::decodeTransform(string str) {
	string posx = "", posy = "", rot = "";
	int i = 2; bool found = false;
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else posx += str[i];
		i++;
	}
	found = false;
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else posy += str[i];
		i++;
	}
	found = false;
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else rot += str[i];
		i++;
	}

	gtr->setPosition(Vector2D(stof(posx), stof(posy)));
	gtr->setRotation(stof(rot));
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

	showHostMessage();

	if (!masterSocket) {
		cerr << "NO HAY MASTER SOCKET" << endl;
		return false;
	}

	sockSet = SDLNet_AllocSocketSet(2);
	SDLNet_TCP_AddSocket(sockSet, masterSocket);

	if (SDLNet_CheckSockets(sockSet, SDL_MAX_UINT32) > 0) {
		if (SDLNet_SocketReady(masterSocket)) {
			sock = SDLNet_TCP_Accept(masterSocket);
			//cout << "SE CONECTO ALGUIEN" << endl;
		}
	}
	SDLNet_TCP_AddSocket(sockSet, sock);
	auto n = name.c_str();
	cout << n << endl;

	SDLNet_TCP_Send(sock, name.c_str(), name.length() + 1);

	SDLNet_TCP_Recv(sock, buffer, 255);
	name = (string)buffer;

	cout << "Se conecto un usuario:" << name << endl;

	host = true;
	connected = true;
	//cout << "TODO BIEN, TODO CORRECTO" << endl;
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
		cout << "> Me conecte al host " << ip.host << " en el puerto " << port << endl;
		sockSet = SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(sockSet, sock);
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

	connected = true;
	masterSocket = nullptr;
}

void NetworkSystem::showHostMessage() {

	SDL_RenderClear(sdlutils().renderer());
	Texture* txt = &sdlutils().msgs().at("WAITING_MSG");
	SDL_Rect r;
	r.x = WIN_WIDTH / 2 - txt->width() / 2;
	r.y = WIN_HEIGHT / 2 - txt->height() / 2;
	r.w = txt->width(); r.h = txt->height();
	txt->render(r);
	SDL_RenderPresent(sdlutils().renderer());
}

void NetworkSystem::disconnect() {
	if (connected) {
		if (host) {
			SDLNet_FreeSocketSet(sockSet);
			SDLNet_TCP_Close(masterSocket);
		}
		SDLNet_TCP_Close(sock);
	}
}

void NetworkSystem::convertInfo(string& str) {
	int i = 0u;
	for (; i < str.size() && i < 255; i++) {
		buffer[i] = str[i];
	}
	buffer[i] = 0;
}

string NetworkSystem::revertInfo() {
	buffer[255] = 0;
	return (string)buffer;
}

void NetworkSystem::decode(string str, char separator) {
	if (str[0] == 'm') {
		decodeTransform(str);
	}

	else if (str[0] == 'r') {
		// MANDAR MENSAJE DE GHOST_ROT con signo (0 negativa, 1 positiva)
		int rot = str[2] - '0';
		Message mes;
		mes.id = _m_GHOST_ROTATED;
		if (rot == 0) mes.ghost_data.sign = -2;
		else mes.ghost_data.sign = 2;
		mngr->send(mes);
	}

	else if (str[0] == 'b') {
		// MANDAR MENSAJE DE GHOST_SHOT
		Message mes;
		mes.id = _m_GHOST_SHOT;
		mngr->send(mes);
	}
}

void NetworkSystem::sendMessages() {

}

void NetworkSystem::recInfo(string str) {

}