#ifndef CRATE_H
#define CRATE_H
#include "Object.h"

class ItemCrate : public Object {
	private:
		sf::Sprite sprite;
		int level; // The higher the level the higher the items obtained.
	public:
		void update(float time);
		void draw();
		void initialize(float width, float height);
		void collision(Object * other, int fixtureID);

		void setLevel(int amount);
};

#endif