#include "Corpse.h"
#include "math.h"
#include "ObjectManager.h"

void Corpse::initialize(float width, float height){
	type = ObjectName::CORPSE;
	sprite.setTexture( *image );
	sf::Vector2u size = sprite.getTexture()->getSize();
	counter = 0;
	sprite.setOrigin( size.x / 2, size.y / 2 );

	if (right)
		sprite.scale(blocksizeToScale(visual->getBlockSize()*width,size.x), blocksizeToScale(visual->getBlockSize()*height, size.y));
	else 
		sprite.scale(-blocksizeToScale(visual->getBlockSize()*width,size.x), blocksizeToScale(visual->getBlockSize()*height,size.y));
	// Set a shape.
	b2PolygonShape box;

	// Try to make Box2D size as an inference to image size.
	box.SetAsBox( width/2 , height/2 );
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = density;
	fixture.friction = friction;
	body->CreateFixture(&fixture);
	body->SetFixedRotation(true);
}

void Corpse::update(float time){
	// Do nothing and be a block.
	counter += time;
	if (counter >= 4){
		manager->remove(ID);
	}
}

void Corpse::draw(){
	sprite.setPosition(x,y);
	visual->registerDraw(&sprite, 2);
}

void Corpse::collision(Object * other, int fixtureID){
	
}

void Corpse::setImage(std::string name){
	image = visual->getTexture(name);
}

void Corpse::setRight(bool r){
	right = r;
}

void Corpse::setFriction(float f){
	friction = f;
}

void Corpse::setDensity(float d){
	density = d;
}

Corpse::Corpse(){
	density = 3;
	friction = 3;
	right = 1;
}