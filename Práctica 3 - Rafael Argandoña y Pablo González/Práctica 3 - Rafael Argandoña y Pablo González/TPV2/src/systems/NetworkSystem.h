#pragma once
#include "../ecs/System.h"
#include "../game/NetworkMessages.h"
#include "../components/Transform.h"

class NetworkSystem : public System{
private:
	bool host;

	IPaddress ip;
	TCPsocket masterSocket;
	TCPsocket sock;
	SDLNet_SocketSet sockSet;
	Uint16 port;

	bool connected;
	char buffer[256];
	int prevNBullets, newNBullets;

	Transform* tr;
	Transform* gtr;
	string name;
	string hostName;

	bool initHost();
	bool initClient();
	void showHostMessage();

	void checkSend(string info);

	string revertInfo();
	void decode(string);
	void sendMessage();
	void decodeMessage(string line);

public:
	static constexpr sysId id = _sys_NETWORK_;

	NetworkSystem();
	~NetworkSystem();

	void receive(const Message& m) override;
	void initSystem() override;
	void update() override;

	bool connect();
	void disconnect();

	inline bool isConnected() { return connected; }
	inline bool isHost() { return host; }
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