#ifndef BOMB1_H
#define BOMB1_H

#include "Object.h"
#include "ParticlesBomb.h"
#include "ParticlesBombfire.h"

class Bomb1 : public Object{
	private:
		sf::Sprite sprite;
		float timer;
		ParticlesBombfire * fire;
	public:
		void update (float time);
		void initialize(float width, float height);
		void draw();
		void setRotation(float r);
};

#endif