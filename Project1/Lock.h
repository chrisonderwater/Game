#ifndef LOCK_H
#define LOCK_H
#include "Object.h"

class Lock : public Object {
private:
	int lockID;
	sf::Sprite sprite;
public:
	void draw();
	void update(float time);
	void initialize(float width, float height);
	void collision( Object* other, int fixtureID);

};


#endif