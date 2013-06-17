#include "server_application.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;

//-------------------------
//Public access members
//-------------------------

ServerApplication::ServerApplication() {
	//
}

ServerApplication::~ServerApplication() {
	//
}

/* ServerApplication::Init()
 * This function initializes the entire program. There are a number of things
 * that could go wrong here, which is why there is such an unusual order of
 * operations.
 * Important things to note:
 *   The APIs are initiated here.
 *   The global objects are created here.
 *   The ConfigUtility's call to Load() also ensures that the "rsc\" folder is in the directory. It's easy to forget it.
*/

void ServerApplication::Init() {
	//load the config file
	try {
		configUtil = ServiceLocator<ConfigUtility>::Set(new ConfigUtility());
		configUtil->Load("rsc/config.cfg");
	}
	catch(std::runtime_error& e) {
		std::string s = e.what();
		s += "; Ensure that the \"rsc\" directory is present";
		throw(std::runtime_error(s));
	}

	//check the port is valid
	if (configUtil->Int("server.port") <= 0) {
		throw(runtime_error("Cannot open the server on an invalid port or port 0"));
	}

	//initialize the APIs
	if (SDLNet_Init()) {
		throw(runtime_error("Failed to initialize SDL_net"));
	}

	//instanciate the remaining services
	netUtil = ServiceLocator<UDPNetworkUtility>::Set(new UDPNetworkUtility());

	//initiate the remaining services
	netUtil->Open(configUtil->Int("server.port"), sizeof(Packet));

	//create the threads
	BeginQueueThread();

	//output the server information
	cout << configUtil->String("server.name") << endl;
	cout << "Open on port " << configUtil->String("server.port") << endl;

	//disable this for debugging
	running = true;
}

void ServerApplication::Proc() {
	Clock::duration delta = Clock::now() - lastTick;
	lastTick = Clock::now();
	while(running) {
		try {
			//process all packets on the network queue
			while(HandlePacket(popNetworkPacket()));
		}
		catch(exception& e) {
			cerr << "Network Error: " << e.what() << endl;
		}
		UpdateWorld(double(delta.count()) / Clock::duration::period::den);
		SDL_Delay(10);
	}
}

void ServerApplication::Quit() {
	//close the threads
	EndQueueThread();

	//clean up the services
	netUtil->Close();

	//delete the services
	configUtil = ServiceLocator<ConfigUtility>::Set(nullptr);
	netUtil = ServiceLocator<UDPNetworkUtility>::Set(nullptr);

	//deinitialize the APIs
	SDLNet_Quit();
}

//-------------------------
//Game loop
//-------------------------

void ServerApplication::UpdateWorld(double delta) {
	for (auto it : players) {
		it.second.Update(delta);
	}
}

//-------------------------
//Network loop
//-------------------------

int ServerApplication::HandlePacket(Packet p) {
	switch(p.meta.type) {
		case PacketType::NONE:
			//DO NOTHING
			return 0;
		break;
		case PacketType::PING:
			//quick pong
			p.meta.type = PacketType::PONG;
			netUtil->Send(&p.meta.address, &p, sizeof(Packet));
		break;
		case PacketType::PONG:
			//
		break;
		case PacketType::BROADCAST_REQUEST:
			Broadcast(p.broadcastRequest);
		break;
//		case PacketType::BROADCAST_RESPONSE:
//			//
//		break;
		case PacketType::JOIN_REQUEST:
			HandleConnection(p.joinRequest);
		break;
//		case PacketType::JOIN_RESPONSE:
//			//
//		break;
//		case PacketType::DISCONNECT:
//			//
//		break;
//		case PacketType::SYNCHRONIZE:
//			//
//		break;
//		case PacketType::PLAYER_NEW:
//			//
//		break;
//		case PacketType::PLAYER_DELETE:
//			//
//		break;
//		case PacketType::PLAYER_MOVE:
//			//
//		break;
		default:
			throw(runtime_error("Failed to recognize the packet type"));
	}
	return 1;
}

void ServerApplication::Broadcast(BroadcastRequest& bcast) {
	//respond to a broadcast request with the server's data
	Packet p;
	p.meta.type = PacketType::BROADCAST_RESPONSE;
	snprintf(p.broadcastResponse.name, PACKET_STRING_SIZE, "%s", configUtil->CString("server.name"));
	//TODO version information
	netUtil->Send(&bcast.meta.address, &p, sizeof(Packet));
}

void ServerApplication::HandleConnection(JoinRequest& request) {
	//create the containers
	ClientData client = { clientTicker++ };
	PlayerData player = { playerTicker++ };

	//link the containers
	client.playerIndex = player.index;
	player.clientIndex = client.index;

	//??? oh fuck
}