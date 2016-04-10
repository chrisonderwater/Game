
#include "RandomBuildingGenerator.h"
#include "ObjectManager.h"
#include "createType.h"
#include <fstream>

void RandomBuildingGenerator::update(float time){
	// Do nothing since I will get destroyed. <3
}

void RandomBuildingGenerator::draw(){
	// Do nothing cause pieces of the map know how to draw itself.
}


// Generate the map!
void RandomBuildingGenerator::initialize(float width, float height){
	buildingHeight = (int) height;
	buildingWidth  = (int) width;
	int plateCounter;
	int platePos;
	int state = 0;
	int k;
	//loadBuilding("resources/building.txt",matrix);
	simpleGenerate(24, 30);
	// state 0 ::: nothing to do
	// state 1 ::: Waiting for another 4.

	for (int i = 0; i  < buildingHeight; i++){
		for( int j = 0; j < buildingWidth; j++){
			if (state == 0){
				if( matrix[i][j] == 2 ){ // If: Pilar1!
					state = 1;
					plateCounter = 1;
					platePos = j;
				} else if( matrix[i][j] == 4 ){ // If: Plate1
					createType(manager, matrix[i][j], body->GetPosition().x + j + 0.5,body->GetPosition().y - 1 - i,1,2, 0);
				}else if(matrix[i][j] == 8){ // If: Ladder
					k = 0;
					while(matrix[i+k][j] == 8){
						matrix[i+k][j] = 0;
						k++;
					}
					createType(manager, 8, body->GetPosition().x + j + 0.5,body->GetPosition().y - 0.5 - i,1,k, 0);
				}
			} else if(state == 1){
					if(matrix[i][j] == 0){
						
						plateCounter++;
					}else if(matrix[i][j] == 2){
						plateCounter++;
						createType(manager, matrix[i][j], body->GetPosition().x + platePos + plateCounter/2 + 0.5  ,body->GetPosition().y - 0.5 - i,plateCounter,1, 0);
						state = 0;
					}
				}
			}
		}
}


void RandomBuildingGenerator::loadBuilding(std::string fileName, int matrix[][200]){
	std::fstream file(fileName);
	int i = 0;
	int j = 0;

	bool first = true;
	char k = file.get();

	while(k != EOF){
		if( k == '\n'){
			if(first){
				first = false;
				buildingWidth = j + 1;
			}
			i += 1;
			j = 0;
		} else {

			// The loadBuilding function 
			matrix[i][j] = k - '0';
			j++;
		}
		k = file.get();
	}

	buildingHeight = i + 1;

}

void RandomBuildingGenerator::simpleGenerate(int width, int height){
	buildingHeight = height;
	buildingWidth  = width;

	BuildingBlock simpleBlock;
	simpleBlock.load("resources/simple_block1.txt");
	//loadBuilding("resources/simple_block1.txt", matrix);

	// Copy simpleBlocks into matrix.
	for(int i=0; i < buildingHeight; i += simpleBlock.height){
		for (int j = 0; j < buildingWidth; j += simpleBlock.width){
			for(int k = 0; k < simpleBlock.height; k++){
				for(int l = 0; l < simpleBlock.width; l++){
					matrix[i+k][j+l] = simpleBlock.matrix[k][l];
				}
			}
		}
	}
}

void BuildingBlock::load(std::string fileName){
	std::fstream file(fileName);
	int i = 0;
	int j = 0;

	bool first = true;
	char k = file.get();

	while(k != EOF){
		if( k == '\n'){
			if(first){
				first = false;
				width = j;
			}
			i += 1;
			j = 0;
		} else {

			// The loadBuilding function 
			matrix[i][j] = k - '0';
			j++;
		}
		k = file.get();
	}

	height = i + 1;
}