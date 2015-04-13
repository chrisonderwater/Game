#ifndef BOMBCONTAINER_H
#define BOMBCONTAINER_H
#include <map>
#include "ObjectNames.h"
#include <SFML/Graphics.hpp>

struct BombContainer {
	BombContainer();
	std::map<ObjectName, int> bombs;
	std::map<ObjectName, std::string> textures;
};

#endif