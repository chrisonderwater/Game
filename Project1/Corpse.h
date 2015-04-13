#ifndef CORPSE_H
#define CORPSE_H
#include "Object.h"
#include <SFML/Graphics.hpp>

// A simple object that makes a dead actor or enemy lay around for some time.

class Corpse : public Object {
private:
	sf::Sprite sprite;
	sf::Texture * image;
	bool right;
	float density;
	float friction;
	float counter;
public:
	Corpse();
	// Inherited virtual functions.
	void initialize(float width, float height);
	void update(float time);
	void draw();
	void collision(Object * other, int fixtureID);

	// Specific functions.
	void setImage(std::string name);
	void setRight(bool r);
	void setDensity(float d);
	void setFriction(float f);
};


#endif