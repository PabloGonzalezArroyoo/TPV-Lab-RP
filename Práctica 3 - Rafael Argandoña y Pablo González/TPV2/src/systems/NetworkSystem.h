#pragma once
#include "../ecs/System.h"
#include "../game/NetworkMessages.h"

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

	string name;
	string hostName;

	bool initHost();
	bool initClient();
	bool initConnection(const Uint16& port);


public:
	static constexpr sysId id = _sys_NETWORK_;

	NetworkSystem();
	~NetworkSystem();

	void receive(const Message& m) override;
	void initSystem() override;

	bool connect();
	void disconnect();

	void convertInfo(string& str);
	void revertInfo(string& str);

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