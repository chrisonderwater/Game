#include "ObjectManager.h"
#include "Explosion.h"
#include "math.h"

void Explosion::initialize(float width, float height){
	step = 0;
	type = ObjectName::EXPLOSION;
	
	b2CircleShape circle;
	circle.m_radius = ((width+height)/2) / 2;	
	//b2PolygonShape circle;
	//circle.SetAsBox(0.4f,0.4f);
	setImpactAmount(10);
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.isSensor = true;
	
	body->CreateFixture(&fixture);
}

void Explosion::update(float time){
	// This object must survive one step.
	if (step == 0){
		step = 1;
	}else {
		manager->remove(ID);
	}
}

void Explosion::draw(){}

// This is the actual formula of the explosion.
// Calculates the amount of impact using impact and distance parameters.
void Explosion::collision(Object * other, int fixtureID){
	float x1 = body->GetPosition().x;
	float y1 = body->GetPosition().y;
	float x2 = other->getBody()->GetPosition().x;
	float y2 = other->getBody()->GetPosition().y;

	float distance = pointDistance(x1,x2,y1,y2);
	float d = pointDirection(x1,x2,y1,y2);
	float i = impactAmount / (3 + distance/2 );	//Explosion formula.
	other->impact(d, i, 1.0f);
}

void Explosion::setImpactAmount(float amount){
	impactAmount = amount;
}