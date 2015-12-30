
#define OBJMN_IMPLEMENTATION

#include "ObjectManager.h"

//Include specific implementations of objects.
#include "Block.h"
#include "Floor.h"
#include "Actor.h"
#include "Block2.h"
#include "Bomb1.h"
#include "Explosion.h"
#include "Enemy1.h"
#include "ItemLife.h"
#include "ItemPoints.h"
#include "Corpse.h"
#include "ItemCrate.h"
#include "Ladder.h"
#include "Lock.h"
#include "Key.h"
#include "Message.h"
#include "RandomBuildingGenerator.h"
#include "Input.h"

#include "ObjectNames.h"
#include "LightsManager.h"

#include <iostream>
ObjectManager::ObjectManager(Renderer * temp){
	renderer = temp;
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContactListener(&listener);
	lightsManager = new LightsManager(world,renderer);
	lightsManager->setLights( renderer->getLights() );
	actorCounter = 0;
	input = new Input;
}

void ObjectManager::addRandomBuildingGenerator(float x, float y, float width, float height){
	Object * temp = new RandomBuildingGenerator;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );

	//Create Box2D body.
	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_staticBody;                // <-- Important for dynamic objects!
	bodyDef.position.Set(x, y);
	temp->setBody( world->CreateBody(&bodyDef) );

	//And initialize the object.
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(width, height);

}
void ObjectManager::addBlock(float x, float y, float width, float height){
	//Create the Actor.
	Object * temp = new Block;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );
	//Create Box2D body.
	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody;                // <-- Important for dynamic objects!
	bodyDef.position.Set(x, y);
	temp->setBody( world->CreateBody(&bodyDef) );
	//And initialize the object.
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(width, height);
}

void ObjectManager::addBlock2(float x, float y, float width, float height){
	//Create the Actor.
	Object * temp = new Block2;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );
	//Create Box2D body.
	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody;                // <-- Important for dynamic objects!
	bodyDef.position.Set(x, y);// Het centrum moet worden meegegeven.
	temp->setBody( world->CreateBody(&bodyDef) );
	//And initialize the object.
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(width, height);
}

void ObjectManager::addFloor(float tempX, float tempY, float tempWidth, float tempHeight){
	//Create the floor Object.
	Object * temp = new Floor;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );
	//Create Box2D body.
	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.position.Set(tempX, tempY );
	temp->setBody(world->CreateBody(&bodyDef ) );
	//And initialize the object.
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(tempWidth, tempHeight);
}

void ObjectManager::addActor(float x, float y){
	Actor * temp = new Actor;
	temp->setActorId(actorCounter);
	actorCounter++;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set(x,y);
	temp->setBody(world->CreateBody(&bodyDef) );
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(1,1);
}


void ObjectManager::update(float time){
	
	input->update();
	//update objects.
	for(int i=0;i<objects.size();i++){
		if (objects[i] != NULL)
			objects[i]->update(time);
	}
	//update box2D
	float32 timeStep = time;
	int32 velocityIterations = 20;//Higher = more precision.
	int32 positionIterations = 20;//Lower = more speed.
	world->Step(timeStep, velocityIterations, positionIterations);
	removeStep();

	lightsManager->update();
}

void ObjectManager::draw(){
	for(int i=0;i<objects.size();i++){
		if (objects[i] != NULL){
			objects[i]->updateBox2d();
			objects[i]->draw();
		}
	}

	lightsManager->draw();
}

void ObjectManager::createWorld(){
	/*b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;
	world = new b2World(gravity);*/
}

void ObjectManager::printAmount(){
	std::cout << std::endl << "Amount: " << objects.size() << std::endl;
}

void ObjectManager::loadBackground(std::string file){
	renderer->setBackground(file);
}

void ObjectManager::remove(const unsigned int id){
	objectsToRemove.push(id);
}

void ObjectManager::rm(const unsigned int id){
	//If actor is removed the actor counter should decrease.
	Object * test;
	if(objects.at(id)->type == ObjectName::ACTOR){
		actorCounter--;
	}

	//Nooit geweten dat h	et zo makkelijk zou zijn ... Meteen gesorteerd.
	if (id < objects.size() ){
		objects.back()->setID(id);
		if (objects.at(id)->getBody() != NULL)
			world->DestroyBody( objects.at(id)->getBody() );
		std::swap(objects.at(id), objects.back() );
		objects.pop_back();
	}

}

void ObjectManager::removeStep(){
	while (!objectsToRemove.empty() ){
		rm( objectsToRemove.top() );
		objectsToRemove.pop();
	}
	while ( !bodytypesToChange.empty() ){
		std::pair<b2Body*, b2BodyType> temp = bodytypesToChange.top();
		temp.first->SetType(temp.second);
		bodytypesToChange.pop();
	}
}
void ObjectManager::addBomb1(float x, float y, float width, float height, float rotation){
	Bomb1 * b = new Bomb1;
	b->setRotation(rotation);
	
	Object* temp = b;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody; 
		//Plaats het object in het midden van de getekende vorm.
	bodyDef.position.Set(x ,y );

	temp->setBody( world->CreateBody(&bodyDef) );
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(1,1);
}

void ObjectManager::addExplosion(float radius, float impact, float x, float y){
	Explosion * e = new Explosion;
	e->setImpactAmount(impact);

	Object * temp = new Explosion;
	objects.push_back(temp);
	objects.back()->setID( objects.size()-1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody; 
		//Plaats het object in het midden van de getekende vorm.
	bodyDef.position.Set( x , y );

	temp->setBody(world->CreateBody(&bodyDef)  );
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(radius, radius);
}

void ObjectManager::addEnemy1(float x, float y){
	Object * temp = new Enemy1;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	temp->setBody(world->CreateBody(&bodyDef)  );
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(1,1);
}

void ObjectManager::setGameStats(GameStats * stats){
	gameStats = stats;
}

void ObjectManager::addItemLife( float x, float y){
	Object * temp = new ItemLife;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = temp;
	bodyDef.position.Set(x, y);

	temp->setBody( world->CreateBody(&bodyDef) );
	temp->setInterfaces( renderer, this, gameStats);
	temp->initialize(1,1);
}

void ObjectManager::addItemPoints( float x, float y, int amount){
	ItemPoints * p = new ItemPoints;
	p->setAmount(amount);
	
	Object * temp = p;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = temp;
	bodyDef.position.Set(x, y);

	temp->setBody( world->CreateBody(&bodyDef) );
	temp->setInterfaces( renderer, this, gameStats);
	temp->initialize(1,1);
}

void ObjectManager::addCorpse(float x, float y, float w, float h, float d, float f, bool r, std::string fileName){
	Corpse * c = new Corpse;
	c->setInterfaces( renderer, this, gameStats );
	c->setDensity(d);
	c->setFriction(f);
	c->setRight(r);
	c->setImage(fileName);

	Object * temp = c;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = temp;
	bodyDef.position.Set(x, y);

	temp->setBody( world->CreateBody(&bodyDef) );
	temp->initialize(w, h);
}

void ObjectManager::addItemCrate(float x, float y, float level){
	ItemCrate * c = new ItemCrate;
	c->setLevel(level);

	Object * temp = c;
	objects.push_back(temp);
	objects.back()->setID(objects.size() - 1);

	b2BodyDef b;
	b.type = b2_dynamicBody;
	b.userData = temp;
	b.position.Set(x, y);
	temp->setBody( world->CreateBody(&b) );
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(0.5f,0.5f);
}
void ObjectManager::addLadder(float x, float y, float width, float height){
	Object * temp = new Ladder;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1 );

	b2BodyDef b;
	b.type = b2_dynamicBody;
	b.userData = temp;
	b.position.Set(x,y);
	temp->setBody( world->CreateBody(&b));
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(width, height);
}

void ObjectManager::addLock(float x, float y){
	Object * temp = new Lock;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	temp->setBody(world->CreateBody(&bodyDef)  );
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(1,1);
}

void ObjectManager::addKey(float x, float y){
	Object * temp = new Key;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1 );

	b2BodyDef bodyDef;
	bodyDef.userData = temp;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	temp->setBody(world->CreateBody(&bodyDef)  );
	temp->setInterfaces(renderer, this , gameStats);
	temp->initialize(1,1);
}

void ObjectManager::addMessage(sf::Texture * texture, float time){
	Message * message = new Message;
	message->setTexture(texture);
	message->setLifetime(time);
	
	Object * temp = message;
	objects.push_back(temp);
	objects.back()->setID( objects.size() - 1);
	
	temp->setInterfaces(renderer, this, gameStats);
	temp->initialize(1,1);
}

void ObjectManager::changeBodytype(b2Body * b, b2BodyType t){
	std::pair<b2Body *, b2BodyType> temp;
	temp.first = b;
	temp.second = t;
	bodytypesToChange.push(temp);
}

void ObjectManager::setInput(Input * input){
	this->input = input;
}

Input * ObjectManager::getInput(){
	return input;
}


