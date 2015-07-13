#ifndef MENU_H
#define MENU_H

#include "Renderer.h"
#include "MenuItem.h"
#include "Game.h"
#include <vector>

class Menu {
private: 
	Renderer * visual;
	Game * game;
	std::vector < MenuItem* > items;
	bool pressed;

	sf::Texture * backgroundTexture;
	sf::Sprite background;
public:
	Menu(Renderer * r, Game * g);
	void update(float time);
	void draw();
	void addExitButton(float j, float i);
	void addPlayButton(float j, float i);
	void addScoreboard(float j, float i);
	void resizeMenu(float width, float height);
	void setBackground(std::string fileName);
};

#endif