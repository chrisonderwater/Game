#include "BombContainer.h"
#include <iostream>
BombContainer::BombContainer(){
	textures[ObjectName::BOMB1] = "resources/textures/bomb.png";

	for(auto iterator = bombs.begin();iterator != bombs.end(); iterator++){
		iterator->second = -1;
	}
}