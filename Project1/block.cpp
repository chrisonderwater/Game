#include "Block.h"
#include "math.h"
#include "ObjectManager.h"
#include <Box2D\Box2D.h>

void Block::initialize(float width, float height){
	type = ObjectName::BLOCK;
	width -= 0.02;
	height -= 0.02;
	// Know the block size magic! :O
	sprite.setTexture( *(visual->getTexture("resources/textures/plaatje.png")) );
	sprite.setOrigin( sprite.getTexture()->getSize().x/2,sprite.getTexture()->getSize().y/2 );
	sprite.scale(width*blocksizeToScale( visual->getBlockSize(),96),height*blocksizeToScale(visual->getBlockSize(),96) );									// <--- experimental!
	health = 3;
	//Create polygonshape.
	b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(width/2, height/2);
	//And set its properties.
	b2FixtureDef fixtureDef;        //A polygon is just a part of a fixture ...
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 2.0f;      // <- Now body will react to its environment.
	fixtureDef.friction = 2.0f;
	//And bind fixture to the body.
	body->CreateFixture(&fixtureDef);

	//body->ApplyAngularImpulse(rand()%10);
}

void Block::update(float time){
	if (health <= 0){
		manager->remove(ID);
	}
}

void Block::draw(){
		sprite.setPosition(x,y);
		sprite.setRotation(radiansToDegrees(rotation));
		visual->registerDraw(&sprite,0);
}

void Block::collision(Object * other, int fixtureID){
	if(other->type == ObjectName::ACTOR){
		
	}
}

void Block::impact(const float direction, const float amount, const float damage){
	if (damage >= 1)
		manager->changeBodytype(body, b2BodyType::b2_dynamicBody);
	b2Vec2 point(0,0);
	b2Vec2 vector = directionPoint(0,0,direction,amount);
	body->ApplyLinearImpulse(vector,point,true);
	health -= damage;
}