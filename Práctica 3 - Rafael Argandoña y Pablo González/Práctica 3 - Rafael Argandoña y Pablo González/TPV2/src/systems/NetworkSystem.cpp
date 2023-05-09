#include "NetworkSystem.h"
#include "../ecs/Manager.h"
#include "../systems/RenderSystem.h"

NetworkSystem::NetworkSystem() : host(false), sock(), sockSet(), port(1), connected(false),
	ip(), prevNBullets(0), newBullet(false) { }

// Destructora
NetworkSystem::~NetworkSystem() {
	SDLNet_TCP_Close(sock);
	if (masterSocket) SDLNet_TCP_Close(masterSocket);
}

// Recibir mensaje
void NetworkSystem::receive(const Message& m) {
	string inf;
	switch (m.id)
	{
		// Inicializacion del estado
		case _m_INIT_STATE:
			tr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
			gtr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_GHOST_FIGHTER));
		break;
		// En caso de que ganemos, se le informa al otro portatil de que ha perdido
		case _m_PLAYER_WINS:
			inf = "p";
			SDLNet_TCP_Send(sock, inf.c_str(), inf.size() + 1);
			break;
		// En el caso de que perdamos se le informa al otro portatil de que ha ganado
		case _m_PLAYER_DAMAGED:
			inf = "w";
			SDLNet_TCP_Send(sock, inf.c_str(), inf.size() + 1);
			break;
		case _m_CREATED_BULLET:
			//inf = "b";
			//SDLNet_TCP_Send(sock, inf.c_str(), inf.size() + 1);
			newBullet = true;
			break;
	}
}

// Inicializa el sistema
void NetworkSystem::initSystem() {
	connect();
}

// Comprueba si el otro portatil manda informacion y manda la necesaria de este
void NetworkSystem::update() {
	try {
		if (SDLNet_CheckSockets(sockSet, 0) > 0) {
			
			if (sock != nullptr && SDLNet_SocketReady(sock)) {
				int result = SDLNet_TCP_Recv(sock, buffer, 255);
				// Si recibo algo, decodifico el mensaje
				if (result > 0) {
					decode(revertInfo());
				}
				// Si no, se perdio la conexion
				else if (result < 0) {
					string err;
					if (host) err = "CONEXIÓN PERDIDA CON EL CLIENTE";
					else err = "CONEXIÓN PERDIDA CON EL HOST";
					throw(err);
				}
			}
		}
	}

	// Manejo de desconexion
	catch (string e) {
		cout << e << endl;
		// Si soy host, desconectamos del cliente, y nos preparamos para recibir uno nuevo
		if (host) {
			disconnect();
			name = hostName;
			initHost();
			mngr->getSystem<RenderSystem>()->changeClientText(name);
		}
		// Si soy cliente, vuelvo al menu principal
		else {
			Message mes;
			mes.id = _m_DISCONNECTION;
			mngr->send(mes, true);
		}
	}
	
	// Manda la informacion al otro portatil
	sendMessage();
}

// Inicializa en el caso de ser host
bool NetworkSystem::initHost() {
	// Abrimos el puerto en este portatil y el masterSocket
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		cerr << "PUERTO NO VALIDO" << endl;
		return false;
	}
	cout << "El puerto disponible es: " << ip.port << endl;
	masterSocket = SDLNet_TCP_Open(&ip);

	if (!masterSocket) {
		cerr << "NO HAY MASTER SOCKET" << endl;
		return false;
	}

	// Mostramos el mensaje esperando
	showHostMessage();

	// Creamos el socketSet y añadimos el masterSocket
	sockSet = SDLNet_AllocSocketSet(2);
	SDLNet_TCP_AddSocket(sockSet, masterSocket);
	// Buscamos el socket Cliente y lo aceptamos
	if (SDLNet_CheckSockets(sockSet, SDL_MAX_UINT32) > 0) {
		if (SDLNet_SocketReady(masterSocket)) {
			sock = SDLNet_TCP_Accept(masterSocket);
		}
	}
	// Lo añadimos al socketSet
	SDLNet_TCP_AddSocket(sockSet, sock);
	// Mandamos el nombre para comprobar el flujo de informacion
	SDLNet_TCP_Send(sock, name.c_str(), name.length() + 1);
	// Recibimos el nombre del cliente
	SDLNet_TCP_Recv(sock, buffer, 255);
	name = (string)buffer;
	// Informamos de que la conexion se consiguio
	cout << "Se conecto un usuario:" << name << endl;

	host = true;
	connected = true;
	return true;
}

// Inicializa en el caso de ser cliente
bool NetworkSystem::initClient() {
	// Pedimos informacion de la ip del host
	int result = 0;
	cout << "\nIntroduce el host:\n>";
	cin >> hostName;
	cout << "\nIntroduce el puerto:\n>";
	cin >> port;

	// Intentamnos conectarnos
	auto h = hostName.c_str();
	auto a = SDLNet_ResolveHost(&ip, h, port);
	ip.port = port;
	// Si no podemos
	if (a < 0) {
		cerr << "ERROR DE CONEXION AL HOST" << endl;
		return false;
	}
	// Si se puede abrimos el socket y nos conectamos en la ip destino
	sock = SDLNet_TCP_Open(&ip);
	// Si no se puede
	if (!sock) {
		cerr << "NO SE HA CONSEGUIDO ESTABLECER LA CONEXION" << endl;
		return false;
	}
	// Si se puede informo y me añado al socketSet
	else {
		cout << "> Me conecte al host " << ip.host << " en el puerto " << port << endl;
		sockSet = SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(sockSet, sock);
	}

	// ESPERAMOS POR CONFIRMACION DE CONEXION (se recibe informacion)
	result = SDLNet_TCP_Recv(sock, buffer, 255);
	// Si no se recibe
	if (result < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	// Si se rechaza
	else if (result == 0) cout << "EL SERVIDOR CERRO LA CONEXION" << endl;
	// Si se recibe
	else {
		hostName = buffer;
		cout << "EL SERVIDOR ACEPTO LA CONEXION. HOSTNAME: " << hostName << endl;
	}

	// Mostramos el nombre y lo mandamos
	cout << "TU NOMBRE ES: " << name.c_str() << endl;
	SDLNet_TCP_Send(sock, name.c_str(), name.length() + 1);

	connected = true;
	masterSocket = nullptr;
	return true;
}

// Metodo que muestra en pantalla el mensaje de espera
void NetworkSystem::showHostMessage() {

	SDL_RenderClear(sdlutils().renderer());
	Texture* txt = &sdlutils().msgs().at(WAITING_MSG);
	SDL_Rect r;
	r.x = WIN_WIDTH / 2 - txt->width() / 2;
	r.y = WIN_HEIGHT / 2 - txt->height() / 2;
	r.w = txt->width(); r.h = txt->height();
	txt->render(r);
	SDL_RenderPresent(sdlutils().renderer());
}

// Devuelve el buffer convertido a string
string NetworkSystem::revertInfo() {
	buffer[255] = 0;
	return (string)buffer;
}

// Manda la informacion necesaria del transform del jugador de este portatil al otro
void NetworkSystem::sendMessage() {
	// Mandamos posicion y rotacion del jugador de este portatil
	string info = "m ";
	info += to_string(tr->getPosition().getX());
	info += " ";
	info += to_string(tr->getPosition().getY());
	info += " ";
	info += to_string(tr->getRotation());

	//// Si el numero de balas cambia (hay mas) se informa de que instancie una nueva
	//newNBullets = mngr->getEntitiesAlive(_grp_BULLETS);
	//if (prevNBullets != newNBullets && prevNBullets < newNBullets) {
	//	info += " ";
	//	info += "s";
	//}
	//prevNBullets = newNBullets;

	if (newBullet) {
		info += " ";
		info += "s";
		newBullet = false;
	}

	// Mandamos el mensaje
	SDLNet_TCP_Send(sock, info.c_str(), info.size() + 1);
}

// Gestiona la informacion recibida del otro portatil
void NetworkSystem::decode(string str) {
	// Si la informacion hace referencia al movimiento
	if (str[0] == 'm') {
		decodeMessage(str);
	}
	// Si la informacion hace referencia a acabar la partida (posible solucion de la perdida de balas)
	else if (str[0] == 'p' || str[0] == 'w') {
		Message mes;
		if (str[0] == 'p') mes.id = _m_PLAYER_DAMAGED;
		else mes.id = _m_PLAYER_WINS;
		mngr->send(mes, true);
	}

	/*else if (str[0] == 'b') {
		Message mes;
		mes.id = _m_GHOST_SHOT;
		mngr->send(mes);
	}*/
}

// Lee la informacion que se recibe del transform del jugador del otro portatil
void NetworkSystem::decodeMessage(string str) {
	// Variables auxiliares
	string posx = "", posy = "", rot = "";
	int i = 2; bool found = false;

	// Leemos la x del vector posicion
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else posx += str[i];
		i++;
	}
	found = false;
	// Leemos la y del vector posicion
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else posy += str[i];
		i++;
	}
	found = false;
	// Leemos la rotacion
	while (!found && i < str.size()) {
		if (str[i] == ' ') found = true;
		else rot += str[i];
		i++;
	}
	// Si aun no acabamos de leer es porque hay que instanciar una bala
	if (i < str.size()) {
		Message mes;
		mes.id = _m_GHOST_SHOT;
		mngr->send(mes);
	}

	// Segun lo que leemos, mandamos las propiedades de la nave enemiga
	Message mes;
	mes.id = _m_GHOST_MOVED;
	mes.ghost_data.x = stof(posx); mes.ghost_data.y = stof(posy);
	mes.ghost_data.rot = stof(rot);
	mngr->send(mes);
}

// Metodo para la conexion inicial
bool NetworkSystem::connect() {
	string choice;
	bool done = false, correct = false;

	// Almacenamos el nombre del jugador
	cout << "Cual es tu nombre?\n>";
	cin >> name;

	// Preguntamos su rol y actuamos en consecuencia
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

// Desconectanmos los sockets
void NetworkSystem::disconnect() {
	if (connected) {
		if (host) {
			SDLNet_FreeSocketSet(sockSet);
			SDLNet_TCP_Close(masterSocket);
		}
		SDLNet_TCP_Close(sock);
	}
}