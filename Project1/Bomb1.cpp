#include "Bomb1.h"
#include "ObjectManager.h"
#include "math.h"
#include "ParticlesBomb.h"

void Bomb1::initialize(float width, float height){
	type = ObjectName::BOMB1;
	timer = 0;
	sprite.setTexture(*visual->getTexture( gameStats->getBombFileName(type) ) );
	//Zet de origin in het midden van het plaatje.
	sf::Vector2u tempWH = visual->getTexture( gameStats->getBombFileName(type) )->getSize();
	sprite.setOrigin(tempWH.x/2, tempWH.y/2);
	sprite.scale(blocksizeToScale(visual->getBlockSize(),192),blocksizeToScale(visual->getBlockSize(),192) );

	b2CircleShape circle;
	circle.m_radius = 0.25f;
	//b2PolygonShape circle;
	//circle.SetAsBox(0.4f,0.4f);

	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.density = 60;
	fixture.friction = 10;
	
	body->CreateFixture(&fixture);

	// initialize particles.
	fire = new ParticlesBombfire(visual);
	visual->addParticleSystem(fire);

	// Beweeg in de meegegeven richting.
	b2Vec2 temp = directionPoint(body->GetPosition().x, body->GetPosition().y, rotation, 0.6);

	body->SetTransform(temp, rotation );

	temp = directionPoint(body->GetPosition().x,body->GetPosition().y, rotation, 0.6);
	body->ApplyLinearImpulse(temp, body->GetPosition(),true);
}

void Bomb1::setRotation(float r){
	rotation = r;
	sprite.setRotation(radiansToDegrees(r) );
}

void Bomb1::update(float time){
	// manage the particle system: 
	// as long as the bomb exists, the fire particles will stay alive:
	//fire->resetTimer();
	//fire->burst(static_cast<int>(time * 30));
	//fire->setEmitter(body->GetPosition().x, body->GetPosition().y, body->GetAngle());

	timer += time;
	if (timer >= 2){//Vernietig jezelf en maak een explosie.
		// Create the explosion object.
		manager->addExplosion(3, 8.0f, body->GetPosition().x, body->GetPosition().y );
		// Create the particle emitter.
		ParticleSystem * temp =  new ParticlesBomb(visual);
		temp->setEmitter(body->GetPosition().x,body->GetPosition().y,rotation);
		temp->burst(50);
		visual->addParticleSystem(temp);
		manager->remove(ID);
	}
}

//Draw a bullet.
void Bomb1::draw(){
	sprite.setPosition( x, y );
	sprite.setRotation(radiansToDegrees(rotation));
	visual->registerDraw(&sprite, 3);
}