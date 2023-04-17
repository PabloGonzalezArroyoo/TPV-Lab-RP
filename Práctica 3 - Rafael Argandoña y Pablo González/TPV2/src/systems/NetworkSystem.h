#pragma once
#include "../ecs/System.h"

class NetworkSystem : public System{
private:
	bool host;
	UDPsocket* sock;
	UDPpacket* pack;
	SDLNet_SocketSet sockSet;
	Uint16 port;

	bool connected;
	IPaddress otherAddr;
public:
	NetworkSystem();

	void receive(const Message& m) override;
	void initSystem() override;
	void update() override;

	bool connect();
	void disconnect();

	inline bool isConnected() { return connected; }
	inline bool isHost() { return host; }
	inline Uint16 getPort() { return port; }


};