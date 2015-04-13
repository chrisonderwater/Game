#include "ExitButton.h"
#include "Game.h"
#include "Renderer.h"

ExitButton::ExitButton(Renderer* r, Game * g, sf::Vector2f pos) {
	visual = r;
	game = g;
	setPosition(pos.x, pos.y);
	sprite.setTexture(*visual->getTexture("resources/textures/exitButton.png") );
	sf::Vector2u s =  visual->getTexture("resources/textures/exitButton.png")->getSize();
	setSize(s.x/visual->getBlockSize(), s.y/visual->getBlockSize() );
}

void ExitButton::draw(){
	visual->registerDraw(&sprite,0);
}

void ExitButton::onPress(){
	// Do none.
}

void ExitButton::onRelease(){
game->endGame();
}