/* Random building generator
   Generates a new building (and thus 95% of the map) randomly.
   This is done using a simple matrix which represents each position.
   Each position in the matrix represents 1 meter in box2d.
   
   - Pilars (where other objects rest upon) have only one position in the matrix but have a height of 2.
     This is represented as: 0 
							 2
	 So it seems as if there is nothing above the pilar but in reality the pilar fills the gap.

   - Plates can vary in size. This is represented as:
     100000001
     The zeros (which normally represent empty space) are in this case filled with the plate.
   - Dynamic objects and items such as packets, keys and enemies will not appear in the matrix.
     Instead they might be generated by chance while generating the building.
	 ( The matrix is no substitute of a map, it's just a tool to make building bricks easy).
   - Prebuilt areas or "rooms" within the building will have to be generated using pre or postprocessing.
     Most likely using preprocessing so that the 'generic' algorithm can fill the gaps afterwards.

*/
#ifndef RAND_BUILDING_GENERATOR
#define RAND_BUILDING_GENERATOR

#include "Object.h"
#include <string>

class RandomBuildingGenerator : public Object{
	public: 
		void update(float time);
		void draw();
		void initialize(float width, float height);
		void loadMap();
		void loadBuilding(std::string fileName, int matrix[][200]);
	private:
		int buildingWidth;
		int buildingHeight;
		int matrix[300][200]; // Temporary matrix used to generate map.
		
};

#endif