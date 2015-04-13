#include "Object.h"
#include "Animation.h"
class Enemy1: public Object{
public: 
	void update(float time);
	void draw();
	void initialize(float width, float height);
	void collision( Object * other, int fixtureID);
	void changeDirection(bool dir);	// 1 = right, 0 = left.
private:
	Animation sprite;
	float turnaroundTimer;
	bool direction;
	bool getDirection();
};