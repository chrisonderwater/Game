#ifndef MESSAGE_H
#define MESSAGE_H

#include "Object.h"
#include <SFML/Graphics.hpp>

class Message : public Object {
private:
	sf::Sprite sprite;
	float lifetime;
	float time;
public:
	void draw();
	void update(float time);
	void initialize(float width, float height);
	void setTexture(sf::Texture * t);
	void setLifetime(float t);
};

#endif