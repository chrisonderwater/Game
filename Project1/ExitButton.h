#include "MenuItem.h"
#ifndef EXITBUTTON_H
#define EXITBUTTON_H

class ExitButton : public MenuItem {
private:

public:
	ExitButton(Renderer * r, Game * g, sf::Vector2f pos);
	void draw();
	void onPress();
	void onRelease();
};

#endif