#ifndef INPUT_H
#define INPUT_H

#include "ObjectManager.h"

// Universal input vars, understandable by all objects.
class InputVars {
	public:
		InputVars();
		void reset();
		int inputId;
		float right;
		float up;
		bool jump;
		bool fire_bomb;
		bool switchBombRight;
		bool switchBombLeft;
};

// Class that transforms input into univsersal input vars.
class Input {
private:
	ObjectManager * objectManager;
	std::vector<InputVars> inputVars;
public:
	Input();
	void update();
	InputVars getInput(int id);

};

#endif