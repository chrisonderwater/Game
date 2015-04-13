#include "Enemy1.h"
#include "math.h"
#include "ObjectManager.h"

/* AI: walk to the right until I hit something. Then turn around. 
   Resembles real world slug pretty well.*/

void Enemy1::initialize(float width, float height){
	turnaroundTimer = 0.0f;
	type = ObjectName::ENEMY1;
	sprite.setTexture(visual->getTexture("resources/textures/slak.png") );
	sprite.getPositionFile("resources/textures/slak.xml");
	sf::Vector2u size = sprite.sprite.getTexture()->getSize();
	health = 1.0f;

	sprite.sprite.setOrigin( size.x / 2, size.y / 2 );
	sprite.setArea(0,50);
	sprite.start();
	sprite.setScale(blocksizeToScale(visual->getBlockSize(),90), blocksizeToScale(visual->getBlockSize(),90));
	direction = false;
	// Set a shape.
	b2PolygonShape box;

	// Try to make Box2D size as an inference to image size.
	box.SetAsBox( width/2 , height/2 );
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 0.5;
	fixture.friction = 2;
	body->CreateFixture(&fixture);
	body->SetFixedRotation(true);
}

void Enemy1::update(float time){
	turnaroundTimer += time;
	sprite.update(time);
	// Test if it's time to, and actually do, turn around.
	if (turnaroundTimer > 2 && getDirection() && body->GetLinearVelocity().x < 0.2f){
		changeDirection(0);
		turnaroundTimer = 0;
	} else if (turnaroundTimer > 2 && !getDirection() && body->GetLinearVelocity().x > -0.2f){
		changeDirection(1);
		turnaroundTimer = 0;
	}

	// Move the slug.
	if (getDirection() && body->GetLinearVelocity().x < 1){
		b2Vec2 force = b2Vec2(0.3f, 0.0f);
		b2Vec2 position = body->GetPosition();
		body->ApplyLinearImpulse(force, position,true);
	} else if(!getDirection() && body->GetLinearVelocity().x > -1){
		b2Vec2 force = b2Vec2(-0.3f, 0.0f);
		b2Vec2 position = body->GetPosition();
		body->ApplyLinearImpulse(force, position,true);
	}

	if (health <= 0){
		manager->addCorpse(body->GetPosition().x, body->GetPosition().y,1,1,5,5,true,"resources/textures/enemy1_corpse.png");
		manager->addItemCrate(body->GetPosition().x+2, body->GetPosition().y-0.2, 0);
		manager->remove(ID);
	}
}

void Enemy1::draw(){
	sprite.sprite.setPosition(x,y);
	visual->registerDraw(&sprite.sprite, 1);
}

void Enemy1::changeDirection(bool dir){
	float s = blocksizeToScale(visual->getBlockSize(), 90);

	if (dir == 0){
		sprite.setScale(s, s);
		direction = 0;
	}else{
		sprite.setScale(-s, s);
		direction = 1;
	}
}

bool Enemy1::getDirection(){
	return direction;
}

void Enemy1::collision(Object * other, int fixtureID){


}