#include "ObjectManager.h"

/*
addObject function.
Adds an object with information from the server.


*/
void ObjectManager::addObject(NetworkObject networkObject){
	switch (networkObject.type){
		case ObjectName::ACTOR:
			// Note: b2d coordinaten of sfml? b2d lijkt logisch..
			addActor(networkObject.x, networkObject.y);

			break;
		default:
			break;
	}

}