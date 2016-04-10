/*

Simpele math functies.

- Richtingen en posities gaan uit van het Box2D coordinaten systeem.
- Er wordt dus gebruik gemaakt van radians ipv. degrees!

*/

#include "math.h"
#include <cmath>
#include <Box2D/Box2D.h>

//Convert radian to degree.
// (Box2D = radians, SFML = degrees!)
float radiansToDegrees(float radians)
{
    float degrees = radians*(180/M_PI);
    return degrees;
}

//Convert degree to radian.
float degreesToRadians(float degrees)
{
    float radians = degrees/(180/M_PI);
    return radians;
}
//--------------------------

// Berekent de richting tussen twee punten.
float pointDirection(int x1, int x2, int y1, int y2){
	 return atan2(y1 - y2, x1 - x2);
}

// Afstand tussen twee punten. Basically Pythagoras.
float pointDistance(int x1, int x2, int y1, int y2){
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

// Geeft bij een bepaalde lengte (speed), en direction, een positie.
// Let op: x, y, en speed zijn in Box2D coordinaten. Dit houdt in dat speed = 1 best groot is. (1 meter per miliseconde ongeveer)
 b2Vec2 directionPoint(float x, float y, float direction, float speed) {
	b2Vec2 point;
	point.x = x - speed*( cos( direction ) );// :O
	point.y = y - speed*( sin( direction ) );

	return point;
 }

 // Returns true if the number is even.
 bool isEven(int number){
	if (number%2)
		return false;
	else
		return true;
 }

 // Higher blockSize means zooming in!
 float blocksizeToScale(int blockSize, int pictureSize){
	return  static_cast<float>(blockSize) / static_cast<float>(pictureSize) ;
 }

 int round(float n){
	return static_cast<int>(n+0.5);
}
