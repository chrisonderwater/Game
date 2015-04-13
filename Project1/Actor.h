#ifndef ACTOR_H
#define ACTOR_H

#include "Object.h"
#include "Animation.h"

class Actor: public Object{
	public:
		void update(float time);
		void draw();
		void initialize(float width, float height);
		void collision(Object * other, int fixtureID);
		void collisionEnd(Object * other, int fixtureID);
	private:
		Animation animation;
		float distance;

		float bombTimer;
		bool jump;
		bool climbing;
		bool right;
		float movementSpeed;

		// Variables for damage control.
		bool damageBool;
		bool showDamage;
		float damageTimer;
		float standingTimer;

};

#endif