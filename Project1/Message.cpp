#include "Message.h"
#include "math.h"
#include "ObjectManager.h"

void Message::draw(){
	sprite.setPosition(x,y);
	visual->registerDraw(&sprite,1);
}

void Message::initialize(float width, float height){
	float s = blocksizeToScale(visual->getBlockSize(), 96);
	sprite.setScale(s,s);
	time = 0.0f;
	body = NULL;
}

void Message::update(float time){
	this->time += time;
	if (this->time > lifetime){
		manager->remove(ID);
	}

	x = visual->getViewPosition().x + visual->getSize().x/2;
	y = visual->getViewPosition().y + visual->getSize().y/3;
}

void Message::setTexture(sf::Texture * t){
	sprite.setTexture(*t);
	sprite.setOrigin(t->getSize().x/2, t->getSize().y/2 );
}

void Message::setLifetime(float t){
	lifetime = t;
}