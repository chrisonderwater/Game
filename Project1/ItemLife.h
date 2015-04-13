#ifndef ITEMLIFE_H
#define ITEMLIFE_H

#include "Object.h"

class ItemLife : public Object {
private:
	sf::Sprite sprite;

public: 
	void initialize(float width, float height);
	void draw();
	void update(float time);
	void impact(const float direction, const float amount, const float damage);
	void collision( Object * other, int fixtureID);
};
#endif