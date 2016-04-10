#ifndef BLOCKLIGHT_H
#define BLOCKLIGHT_H

#include "Object.h"

class BlockLight: public Object{
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