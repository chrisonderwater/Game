
#ifndef NETWORK_H
#define NETWORK_H


#include <SFML/Network.hpp>
#include "definitions.h"
#include "ObjectManager.h"
#include <iostream>
// Network module.
// Layer between game and server.

class Network{
	private:
		sf::UdpSocket * socket;
		ObjectManager * manager;

		//Connection
		std::string ip;
		int         port;


		// Lost packet control.
		sf::Packet * sentPackets[256];
		int          amountLookBack; // Will check if the past *amountLookBack* packets have been received.
		int          lookBackCounter;

		//packets.
		sf::Packet packetDelta;      // Strong object changed positions, transformations, graphics
		sf::Packet packetMessages;   // Everything else ^tm. Mostly important messages that must be received.
		sf::Packet packetImpulses;   // b2d impulses, basically for client side prediction.
		sf::Packet packetVisual;     // maybe a standardized method for visual effects.

		std::vector<NetworkObject*> previousObjects;


	public:
		Network();
		~Network();
		void initialize(ObjectManager * manager);
		void sendPackets();
		void assemblePacketDelta();
		void objectsToPreviousObjects(std::vector< Object * > objects);

		// Messages
		void addMessageConnect();
};










#endif