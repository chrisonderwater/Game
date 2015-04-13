#include "ItemPoints.h"
#include "ObjectManager.h"
#include "math.h"

void ItemPoints::initialize(float width, float height){
	type = ObjectName::ITEM_POINTS;

	sf::Texture * t;
	if (amountPoints >= 20){
		t = visual->getTexture("resources/textures/item_points_20.png");
	}else if(amountPoints >= 10){
		t = visual->getTexture("resources/textures/item_points_10.png");
	} else {
		t = visual->getTexture("resources/textures/item_points_5.png");
	}

	sprite.setTexture( *t );


	sprite.setOrigin(t->getSize().x/2, t->getSize().y/2);
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

void ItemPoints::update(float time){
	if (health <= 0) {
		manager->remove(ID);
	} else if ( health <= 2) {
		body->SetType(b2_dynamicBody);
	}
}

void ItemPoints::draw(){
	sprite.setPosition(x,y);
	sprite.setRotation( radiansToDegrees(body->GetAngle() ) );
	visual->registerDraw(&sprite, 7); // Items have high priority.
}

void ItemPoints::impact(const float direction, const float amount, const float damage){
	// Do nothing. 
	health -= damage;
}

void ItemPoints::collision( Object * other, int fixtureID){
	if (other->type == ObjectName::ACTOR){
		gameStats->addScore(amountPoints);
		manager->remove(ID);
	}
}

void ItemPoints::setAmount(int amount){
	amountPoints = amount;
}