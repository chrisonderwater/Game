#include "MapLoader.h"
#include "ObjectManager.h"
#include "math.h"
#include <fstream>
#include <cmath>
#include "helperFunctions.h"

MapLoader::MapLoader(ObjectManager * m){
	manager = m;
}
//Laadt de map in de huidige objectmanager.
bool MapLoader::load(std::string fileName){
	float locationX;
	float locationY;
	float locationWidth;
	float locationHeight;
	int type=0;
	float parameter = 0;

	reader.read(fileName);
	manager->loadBackground(  reader.getParameterValue("header", "background")  );

	for (int i=0; i<reader.elements.key.size(); i++){
		if (reader.elements.key.at(i) == "objects"){
			for(int j=0;j<reader.elements.value.at(i).key.size();j++){
				if (reader.elements.value.at(i).key.at(j) == "location"){
					locationX = std::stof(  reader.commaExtract( reader.elements.value.at(i).value.at(j)  ,0) );
					locationY = std::stof(  reader.commaExtract( reader.elements.value.at(i).value.at(j)  ,1) );
					locationWidth = std::stof(  reader.commaExtract( reader.elements.value.at(i).value.at(j)  ,2) );
					locationHeight = std::stof(  reader.commaExtract( reader.elements.value.at(i).value.at(j)  ,3) );
				}//if
				else if (reader.elements.value.at(i).key.at(j) == "type"){
					type = std::stoi(reader.elements.value.at(i).value.at(j));
				}else if (reader.elements.value.at(i).key.at(j) == "parameter"){
					parameter = std::stof(reader.elements.value.at(i).value.at(j));
				}//if
			}//for
			createType(type,locationX + locationWidth/2,locationY + locationHeight/2, locationWidth, locationHeight, parameter );
		}//if
	}//for
	return 1;
}//load

//Switch that places objects in the map.
void MapLoader::createType(const unsigned int type, const float x, const float y, const float width, const float height, const float parameter){

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
	}
}