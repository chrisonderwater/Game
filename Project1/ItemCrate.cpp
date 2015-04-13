#include "ItemCrate.h"
#include "math.h"
#include "ObjectManager.h"

void ItemCrate::update(float time){
	if (health <= 0){
		manager->remove(ID);
	}
}

void ItemCrate::draw(){
	sprite.setPosition(x,y);
	visual->registerDraw(&sprite, 4);
}

void ItemCrate::initialize(float width, float height){
	type = ObjectName::ITEM_CRATE;
	sprite.setTexture(*visual->getTexture("resources/textures/ItemCrate.png") );
	float w = visual->getTexture("resources/textures/ItemCrate.png")->getSize().x;
	float h = visual->getTexture("resources/textures/ItemCrate.png")->getSize().x;
	float s = blocksizeToScale(visual->getBlockSize(),353);
	sprite.setOrigin( w/2, h/2);
	sprite.setScale( s, s );
	health = 3;

	b2PolygonShape shape;
	shape.SetAsBox(width/2, height/2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 5;
	fixture.friction = 5;

	body->CreateFixture(&fixture);

}

void ItemCrate::collision(Object * other, int fixtureID){
	if (other->type == ObjectName::ACTOR){

		manager->remove(ID);
	}
}

void ItemCrate::setLevel(int amount){
	level = amount;
}