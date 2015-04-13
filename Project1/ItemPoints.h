#ifndef ITEMPOINTS_H
#define ITEMPOINTS_H

#include "Object.h"

class ItemPoints : public Object {
private:
	sf::Sprite sprite;
	int amountPoints;
public: 
	void initialize(float width, float height);
	void draw();
	void update(float time);
	void setAmount(int amount);
	void impact(const float direction, const float amount, const float damage);
	void collision( Object * other, int fixtureID);
};
#endif