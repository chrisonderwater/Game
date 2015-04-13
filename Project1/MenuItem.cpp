#include "MenuItem.h"
#include "Renderer.h"

sf::Vector2f MenuItem::getSize(){
	return size;
}

sf::Vector2f MenuItem::getPosition(){
	return position; 
}

// B2 coordinates!
void MenuItem::setPosition(float x, float y){
	position.x = x;
	position.y = y;
	sprite.setPosition(x*visual->getBlockSize(),y*visual->getBlockSize() );
}

// B2 coordinates!
void MenuItem::setSize(float w, float h){
	size.x = w ;
	size.y = h ;
}