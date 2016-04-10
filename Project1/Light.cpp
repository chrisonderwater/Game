#include "Light.h"

Light::Light(float x, float y, float brightness, sf::Color color, float rotation, float radius){
	this->x          = x;
	this->y          = y;
	this->brightness = brightness;
	this->color      = color;
	this->rotation   = rotation;
	this->radius     = radius;
}

void Light::setID(int id){
	this->id = id;
}