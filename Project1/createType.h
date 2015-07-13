/*
This is a generic function (distracted from MapLoader.cpp) that allows for 
creating objects using a number. This is for example useful in:
- Map loaders
- Networking
- Random map generators.

*/
#ifndef CREATETYPE_H
#define CREATETYPE_H

#include "ObjectManager.h"

inline void createType(ObjectManager * manager, const unsigned int type, const float x, const float y, const float width, const float height, const float parameter){

	switch(type){
		case 1:
			manager->addActor(x,y);
			break;
		case 2:
			manager->addBlock(x,y,width,height);
			break;
		case 3:
			manager->addFloor(x,y,width,height);
			break;
		case 4:
			manager->addBlock2(x,y,width,height);
			break;
		case 5:
			manager->addEnemy1(x , y);
			break;
		case 6:
			manager->addItemLife(x, y);
			break;
		case 7:
			manager->addItemPoints(x,y, parameter);
			break;
		case 8:
			manager->addLadder(x,y,width, height);
			break;
		case 9:
			manager->addLock(x,y);
			break;
		case 10:
			manager->addKey(x,y);
			break;
		case 11:
			//Add random map generator.
			manager->addRandomBuildingGenerator(x,y,width,height);
			break;
	}
}

#endif