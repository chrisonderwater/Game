#ifndef KEY_H
#define KEY_H
#include "Object.h"

class Key : public Object {
private:
	sf::Sprite sprite;
	int keyID;
public:
	void draw();
	void update(float time);
	void initialize(float width, float height);
	void collision(Object * other, int fixtureID);
};

#endif