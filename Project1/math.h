//Simple math library.
#ifndef MATH_H
#define MATH_H
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062
#include <Box2D\Box2D.h>

//Convert radian to degree.
float radiansToDegrees(float radians);

//Convert degree to radian.
float degreesToRadians(float degrees);

float pointDirection(int x1, int x2, int y1, int y2);

float pointDistance(int x1, int x2, int y1, int y2);

b2Vec2 directionPoint(float x, float y,float direction, float speed);

bool isEven(int number);
int round(float n);

float blocksizeToScale(int blockSize, int pictureSize);
#endif