#include "Input.h"

#include <SFML/Graphics.hpp>
#include <iostream>

InputVars::InputVars(){
	reset();
}

void InputVars::reset(){
	right = 0.0;
	up = 0.0;
	jump = 0;
	fire_bomb = 0;
	switchBombLeft = 0;
	switchBombRight = 0;
}

Input::Input(){
	inputVars.resize(5);
}
// Primitive update method for input.
void Input::update(){
	for(int i=0;i<5;i++){
		inputVars[i].reset();
		inputVars[i].inputId = i;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		inputVars[0].right = 1.0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		inputVars[0].right = -1.0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		inputVars[0].up = -1.0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		inputVars[0].up = 1.0;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		inputVars[0].fire_bomb = 1;

	float movY, movX;
	if (sf::Joystick::isConnected(0)){
		movY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		movX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		movX = movX / 100.0f;
		movY = movY / 100.0f;
		if( sf::Joystick::isButtonPressed(0, 0) ){
			inputVars[1].fire_bomb = 1;
		}
		inputVars[1].up = movY;
		inputVars[1].right = movX;
	}


}

InputVars Input::getInput(int id){
	return inputVars[id];
}

