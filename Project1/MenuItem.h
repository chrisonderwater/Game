#ifndef MENUITEM_H
#define MENUITEM_H

#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class MenuItem {
protected:
	sf::Sprite sprite;
	Game * game;
	Renderer* visual;
	sf::Vector2f position;
	sf::Vector2f size;
public:
	virtual void draw(){};
	virtual void onPress(){};
	virtual void onRelease(){};
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void setSize(float w, float h);
};

#endif