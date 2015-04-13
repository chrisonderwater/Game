#include "PlayButton.h"
#include "Game.h"
#include "Renderer.h"

PlayButton::PlayButton(Renderer * r, Game * g, sf::Vector2f pos) {
	visual = r;
	game = g;
	setPosition(pos.x, pos.y);
	sprite.setTexture(*visual->getTexture("resources/textures/play.png") );
	sf::Vector2u s =  visual->getTexture("resources/textures/play.png")->getSize();
	setSize(s.x/visual->getBlockSize(), s.y/visual->getBlockSize() );
}

void PlayButton::draw(){
	visual->registerDraw(&sprite,1);
}

void PlayButton::onPress(){
	std::cout << "\nPRESS!";
}

void PlayButton::onRelease(){
	GameState state = GameState::GAME;
	game->changeState(state);
	std::cout << "\nRELEASE!";
}