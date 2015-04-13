#include "Menu.h"
#include "PlayButton.h"
#include "ExitButton.h"
#include "ScoreBoard.h"


// The menu is initialized in the constructor.
// Not very portable.
Menu::Menu(Renderer * r, Game * g){
	visual = r;
	game = g;
	pressed = 0;

}

void Menu::update(float time){
	sf::Vector2i mousePosition = visual->getMousePosition();
	float b = visual->getBlockSize();

	// Check all of the bounding boxes !
	if (visual->getMousePressed() && pressed == false){
		for (int i=0;i<items.size();i++){
			sf::Vector2f size = items.at(i)->getSize();
			sf::Vector2f position = items.at(i)->getPosition();
			if (mousePosition.x > position.x*b && mousePosition.x < (position.x*b + size.x*b) && mousePosition.y > position.y*b && mousePosition.y < (position.y*b + size.y*b) ){
				items.at(i)->onPress();
			}
		}
		pressed = true;
	} else if(!visual->getMousePressed() && pressed == true){
		for (int i=0;i<items.size();i++){
			sf::Vector2f size = items.at(i)->getSize();
			sf::Vector2f position = items.at(i)->getPosition();
			if (mousePosition.x > position.x*b && mousePosition.x < (position.x*b + size.x*b) && mousePosition.y > position.y*b && mousePosition.y < (position.y*b + size.y*b) ){
				items.at(i)->onRelease();
			}
		}
		pressed = false;
	}
}

void Menu::draw(){
	for (int i=0;i<items.size();i++){
		items.at(i)->draw();
	}
}

void Menu::addExitButton(float j, float i){
	sf::Vector2f pos;
	pos.x = j;
	pos.y = i;
	items.push_back(new ExitButton(visual,game,pos)  ); 
}

void Menu::addPlayButton(float j, float i){
	sf::Vector2f pos;
	pos.x = j;
	pos.y = i;
	items.push_back(new PlayButton(visual,game,pos)  ); 
}

void Menu::addScoreboard(float j, float i){
	sf::Vector2f pos;
	pos.x = j;
	pos.y = i;
	items.push_back(new ScoreBoard(visual, game, pos) );
}