#include "MenuItem.h"
#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

class PlayButton : public MenuItem {
private:

public:
	PlayButton(Renderer * r, Game * g, sf::Vector2f pos);
	void draw();
	void onPress();
	void onRelease();
};

#endif