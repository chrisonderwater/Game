#include "Lock.h"
#include "math.h"
#include "selectColor.h"

void Lock::draw(){
		sprite.setPosition(x,y);
		sprite.setRotation(radiansToDegrees(rotation));
		visual->registerDraw(&sprite,0);
}
void Lock::update(float time){

}
void Lock::initialize(float width, float height){
	type = ObjectName::LOCK;
	health = 5.0f;
	sprite.setTexture( *visual->getTexture("resources/textures/lock.png"));
	sprite.setOrigin( sprite.getTexture()->getSize().x/2,sprite.getTexture()->getSize().y/2 );
	float s = blocksizeToScale(visual->getBlockSize(), 192);
	sprite.setScale(s,s);
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.75f);
	b2FixtureDef f;
	f.shape = &box;
	f.density = 3.0f;
	f.friction = 5.0f;
	
	body->CreateFixture(&f);

	//Add lock.
	lockID = gameStats->addLock();
	sprite.setColor(selectColor(lockID));
}

void Lock::collision( Object* other, int fixtureID){
	if(other->type == ObjectName::ACTOR){
		gameStats->unlock(lockID);
	}
}