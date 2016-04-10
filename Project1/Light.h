#ifndef LIGHT_H
#define LIGHT_H
#include <SFML\Graphics.hpp>

class Light{
public:
	int id;
	float x;
	float y;
	float brightness;
	sf::Color color;
	float rotation;
	float radius;
	Light(float x, float y, float brightness, sf::Color color, float rotation, float radius);
	void setID(int id);
};


#endif