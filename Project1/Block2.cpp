#include "Block2.h"
#include "math.h"
#include "ObjectManager.h"
#include <Box2D/Box2D.h>

void Block2::initialize(float width, float height){
	type = ObjectName::BLOCK2;
	width -= 0.02;
	height -= 0.02;
	sf::Texture * t = visual->getTexture("resources/textures/muur1.png");
	sprite.setTexture(*t);
	float s = blocksizeToScale(visual->getBlockSize(), 114);
	sprite.setScale(s,s);
	sprite.setOrigin( t->getSize().x/2, t->getSize().y/2 );
	health = 4;
	//Create polygonshape.
	b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(width/2, height/2);
	//And set its properties.
	b2FixtureDef fixtureDef;        //A polygon is just a part of a fixture ...
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;      // <- Now body will react to its environment.
	fixtureDef.friction = 2.0f;
	//And bind fixture to the body.
	body->CreateFixture(&fixtureDef);

	//body->ApplyAngularImpulse(rand()%10);
}

void Block2::update(float time){
	if (health <= 0){
		manager->remove(ID);
	}
}

void Block2::draw(){
		sprite.setPosition(x,y);
		sprite.setRotation(radiansToDegrees(rotation));
		visual->registerDraw(&sprite,0);
}

void Block2::collision( Object * other, int fixtureID){

}

void Block2::impact(const float direction, const float amount, const float damage){
	if (damage >= 1)
		manager->changeBodytype(body, b2BodyType::b2_dynamicBody);
	b2Vec2 point(0,0);
	b2Vec2 vector = directionPoint(0,0,direction,amount);
	body->ApplyLinearImpulse(vector,point,true);
	health -= damage;
}

