#ifndef FLOOR_H
#define FLOOR_H
#include "Object.h"

class Floor : public Object {
	public:
		void update(float time);
		void draw();
		void initialize(float width, float height);
		void impact(const float direction, const float amount, const float damage);
	private:
		sf::RectangleShape rectangle;
};


#endif