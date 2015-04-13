#include "ItemLife.h"
#include "ObjectManager.h"
#include "math.h"

void ItemLife::initialize(float width, float height){
	type = ObjectName::ITEM_LIFE;
	sprite.setTexture( *visual->getTexture("resources/textures/itemLife.png") );
	sprite.setOrigin(visual->getTexture("resources/textures/itemLife.png")->getSize().x/2, visual->getTexture("resources/textures/itemLife.png")->getSize().y/2);
	sprite.setScale( blocksizeToScale(visual->getBlockSize(), 192), blocksizeToScale(visual->getBlockSize(), 192) );

	b2CircleShape circle;
	circle.m_radius = 0.25;	// An item has a size of 0.5
	b2FixtureDef def;
	def.shape = &circle;
	def.density = 2;
	def.friction = 2;
	body->CreateFixture(&def);
	body->SetType(b2_staticBody);

	health = 3;
}

void ItemLife::update(float time){
	if (health <= 0) {
		manager->remove(ID);
	} else if ( health <= 2) {
		body->SetType(b2_dynamicBody);
	}
}

void ItemLife::draw(){
	sprite.setPosition(x,y);
	sprite.setRotation( radiansToDegrees(body->GetAngle() ) );
	visual->registerDraw(&sprite, 7); // Items have high priority.
}

void ItemLife::impact(const float direction, const float amount, const float damage){
	// Do nothing. 
	health -= damage;
}

void ItemLife::collision( Object * other, int fixtureID){
	if (other->type == ObjectName::ACTOR){
		gameStats->addLifes(1);
		manager->remove(ID);
	}
}