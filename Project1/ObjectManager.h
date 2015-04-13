#ifndef OBJMN_H
#define OBJMN_H
/*
ObjectManager has multiple tasks:
	-Organising game objects.
	-Binding them to Box2D
	-Managing Box2D.
	-Abstracting Box2D. (Only Objectmanager and the objects have to understand box2d.)
	This can't easily be distinguished any further since game objects and box2D objects are very close.
	Each game object has an accompanying Box2D object.
*/

#include "ContactListener.h"
#include "Object.h"
#include <vector>
#include <stack>
#include "Renderer.h"
#include <Box2D\Box2D.h>


class ObjectManager {
	private:
		std::vector< Object * > objects;
		std::stack<unsigned int> objectsToRemove;
		std::stack< std::pair<b2Body*, b2BodyType> > bodytypesToChange;
		b2World * world;
		ContactListener listener; //Specific for this manager.
		LightsManager * lightsManager;
		Renderer * renderer;
		GameStats * gameStats;
		void removeStep();
		void rm(const unsigned int id);
	public:
		ObjectManager( Renderer * temp);

		//Functions that add a specific object.
		void addBlock(float x, float y, float width, float height);
		void addBlock2(float x, float y, float width, float height);
		void addFloor(float tempX, float tempY, float tempWidth, float tempHeight);
		void addActor(float x, float y);
		void addBomb1(float x, float y, float width, float height, float rotation);
		void addExplosion(float radius, float impact, float x, float y);
		void addEnemy1(float x, float y);
		void addCorpse(float x, float y, float w, float h, float d, float f, bool r, std::string fileName);
		void addLadder(float x, float y, float width, float height);
		void addLock(float x, float y);
		void addKey(float x, float y);
		void addMessage(sf::Texture * texture, float time);
		// Items.
		void addItemLife(float x, float y);
		void addItemPoints(float x, float y, int amount);
		void addItemCrate(float x, float y, float level);

		void changeBodytype(b2Body * b, b2BodyType t);
		void setGameStats( GameStats * stats);
		void loadBackground(std::string file);
		void remove(const unsigned int id);
		void update(float time);
		void draw();
		void createWorld();
		void printAmount();
};
#endif