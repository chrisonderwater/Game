/*
Universal object. Parent class that makes an object able to function in the engine.

This is the object that binds a box2d body to an object, and thus to the game engine.
Keeps attributes and methods of an object that has an active function in the game.
i.e. interacts with other objects!

After trying to implement the perfect flexible engine the approach partly changed to a
'keep it simple stupid' approach. This means that the engine will NOT take care
of the input, this will be handled by individual objects. This approach seems
to be necessary to keep the C++ understandable. 
*/

#ifndef OBJECT_H
#define OBJECT_H
/*
This class "Object" might as well have been called: Box2D object since
half of the functionality is keeping track of Box2D stuff.
*/
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Renderer.h"
#include "ObjectNames.h"
#include "GameStats.h"

//It was so simple... it was a forward declaration....
class ObjectManager;

class Object{
	protected:
		int ID;		//Position in the big list.
		float health;
		float x;
		float y;
		float rotation;
		Renderer * visual;
		b2Body * body;
		ObjectManager * manager;
		GameStats * gameStats;
	public:
		virtual void initialize(float width, float height)=0;
		virtual void update(float time)=0;
		virtual void draw(){};
		virtual void collision(Object * other, int fixtureID){};
		virtual void collisionEnd(Object * other, int fixtureID){};

		virtual void impact(const float direction, const float amount, const float damage);
		void updateBox2d();
		void setBody( b2Body * temp);
		void setInterfaces( Renderer * render, ObjectManager * mng, GameStats * gameStats);
		void setID(const unsigned int tempID);
		b2Body * getBody();
		ObjectName type;
};

#endif