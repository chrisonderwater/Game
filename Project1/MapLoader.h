#ifndef MAPL_H
#define MAPL_H
#include <string>
#include<memory>
#include "INIReader.h"

class ObjectManager;

class MapLoader{
private:
	INIReader reader;
	ObjectManager * manager;
	char file;
public:
	//Constructor. Initialiseert de maploader.
	MapLoader( ObjectManager * m);
	//Laad een bepaalde file. Returnt false als het mislukt.
	bool load(std::string fileName);
	
};
#endif