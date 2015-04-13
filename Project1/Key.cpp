#include "Key.h"
#include "math.h"
#include "ObjectManager.h"
#include "selectColor.h"
#include "ObjectManager.h"

void Key::draw(){
	sprite.setPosition(x,y);
	sprite.setRotation(radiansToDegrees(rotation));
	visual->registerDraw(&sprite, 2);
}

void Key::update(float time){

}

void Key::collision(Object * other, int fixtureID){
	if(other->type == ObjectName::ACTOR){
		gameStats->keyObtained(keyID);
		manager->remove(ID);
		manager->addMessage(visual->getTexture("resources/textures/Message_key.png"),3.0f);
	}
}

void Key::initialize(float width, float height){
	type = ObjectName::KEY;
	health = 4;
	//Initialize sprite.
	sprite.setTexture( *visual->getTexture("resources/textures/key.png") );
	float s = blocksizeToScale(visual->getBlockSize(), 256);
	sprite.setScale(s,s);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y /2 );
	//Initialize body.
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	b2FixtureDef f;
	f.shape = &shape;
	f.friction = 0.5f;
	f.density = 0.5f;
	body->CreateFixture(&f);
	//Add key to gameStats.
	keyID = gameStats->addKey();
	sprite.setColor(selectColor(keyID));
}