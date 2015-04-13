#ifndef BOMB2_H
#define BOMB2_H

#include "Object.h"
#include "ParticlesBomb.h"
class Bomb2 : public Object{
	private:
		sf::Sprite sprite;
		float timer;
	public:
		void update (float time);
		void initialize(float width, float height);
		void draw();
		void setRotation(float r);
};

#endif