/*
Block 2 is a block where you can walk through.
*/

#ifndef BLOCK2_H
#define BLOCK2_H
#include "Object.h"

class Block2: public Object{
	public:
		void update(float time);
		void draw();
		void initialize(float width, float height);
		void collision( Object* other, int fixtureID);
		void impact(const float direction, const float amount, const float damage);
	private:
		sf::Sprite sprite;
};

#endif