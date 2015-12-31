#include "Actor.h"
#include "ObjectManager.h"
#include "math.h"
#include "ObjectNames.h"
#include "Input.h"

void Actor::initialize(float width, float height){
	type = ObjectName::ACTOR;
	health = 3;
	movementSpeed = 10.0f;
	animation.setTexture(visual->getTexture("resources/textures/karakter.png"));
	animation.getPositionFile("resources/textures/karakter.xml");
	animation.setArea(0,30);
	float s = blocksizeToScale(visual->getBlockSize(), 360);
	animation.setScale(s, s);
	right = 1;
	jump = true;
	climbing = false;
	gameStats->addLifes(3);
	gameStats->addScore(10);

	//Set a shape.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.2f,0.4f);
	//Create a fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox; 
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.userData = (void *)1;

	//Create a jump sensor.
	b2PolygonShape littlebox;
	littlebox.SetAsBox(0.05f,0.05f, b2Vec2(0,0.4f),0);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &littlebox; 
	fixtureDef2.isSensor = true;
	fixtureDef2.userData = (void *)2;
	//The body is managed by objectManager. 
	body->CreateFixture(&fixtureDef);
	body->CreateFixture(&fixtureDef2);
	body->SetFixedRotation(true);
	bombTimer = 0;
	standingTimer = 0;
	// damage control.
	damageBool = false;
	damageTimer = 0;
	showDamage = false;

	Light light(25, 5, 1,sf::Color(255,255,255,40),90.0f,90.0f);

	visual->addLight( light );
	input = manager->getInput();

}

void Actor::update(float time){
	b2Vec2 movement = body->GetLinearVelocity();
	animation.update(time);
	visual->setViewCenter(x,y);

	float movX, movY;
	movX = 0.0f;
	movY = 0.0f;

	InputVars inputVars = input->getInput(0);
		 if(climbing){
			 movY = inputVars.up;
		 }

		movX = inputVars.right;
		movY = inputVars.up;

	// --- end input part

	//key shit
	if(movX > 0.0f && body->GetLinearVelocity().x < 4){
		b2Vec2 force = b2Vec2(movX*2.0f, 0.0f);
		if(climbing){
			force = b2Vec2(10.0f*movX, 0.0f);
		}
		b2Vec2 position = body->GetPosition();
		body->ApplyLinearImpulse(time*movementSpeed*force,position,true);
		float s = blocksizeToScale(visual->getBlockSize(), 360);
		animation.setScale(s,s);
		animation.setArea(0,30);
		animation.setFPS(60);
		animation.setLoop(true);
		animation.start();
		right = 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
		Light light(body->GetPosition().x, body->GetPosition().y, 1,sf::Color(255,255,255,40),315.0f,90.0f);

		visual->addLight( light );
	}
	if(movY < -0.9f && body->GetLinearVelocity().y < 5 && jump && !climbing){
		b2Vec2 force = b2Vec2(0.0f, movY*10);
		b2Vec2 vertical = b2Vec2(body->GetLinearVelocity().x, 0.0f);
		b2Vec2 position = body->GetPosition();
		body->SetLinearVelocity(vertical);
		body->ApplyLinearImpulse(force, position,true);
		if (jump)
			animation.rewind();
		jump = false;
		animation.setArea(235,15);
		animation.setFPS(120);
		animation.start();
		animation.setLoop(false);
	} else if(movY < -0.9f && climbing){
		animation.start();
		if (body->GetLinearVelocity().y > -3){
			b2Vec2 force = b2Vec2(0.0f, -5.0f);
			b2Vec2 position = body->GetPosition();
			body->ApplyLinearImpulse(time*movementSpeed*force, position,true);
		}
	}else if (climbing) {
		b2Vec2 v (body->GetLinearVelocity().x/1.4,0.0f);
		body->SetLinearVelocity(v);
	}

	if(movY > 0.9f && climbing){
		animation.start();
		if (body->GetLinearVelocity().y < 5){
			b2Vec2 force = b2Vec2(0.0f, movY*8.0f);
			b2Vec2 position = body->GetPosition();
			body->ApplyLinearImpulse(movementSpeed*force, position,true);
		}
	}
	if(movX < 0.0f && body->GetLinearVelocity().x > -4){
		b2Vec2 force = b2Vec2(2.0f*movX, 0.0f);
		if(climbing){
			force = b2Vec2(10.0f*movX, 0.0f);
		}
		b2Vec2 position = body->GetPosition();
		body->ApplyLinearImpulse(time*movementSpeed*force, position,true);
		float s = blocksizeToScale(visual->getBlockSize(), 360);
		animation.setScale(-s,s);
		animation.setArea(0,30);
		animation.setFPS(60);
		animation.setLoop(true);
		animation.start();
		right = 0;
	}


	if( (body->GetLinearVelocity().x > -1.0f && body->GetLinearVelocity().x < 1.0f) && standingTimer < 5.0f && jump){
		animation.stop();

		standingTimer += time;
	}else if ((body->GetLinearVelocity().x > -1.0f && body->GetLinearVelocity().x < 1.0f) && standingTimer >= 5.0f && jump && !climbing){
		animation.setArea(55,120);
		animation.setFPS(40);
		animation.start();
		animation.setLoop(true);
	} else if(jump){
		standingTimer = 0.0f;
		animation.setArea(0,30);
		animation.setFPS(60);
		animation.setLoop(true);
	}
	if ( (body->GetLinearVelocity().y > -0.05f && body->GetLinearVelocity().y < 0.05f) && climbing){
		animation.stop();
	} else if(climbing){
		animation.start();
	}

	if(inputVars.fire_bomb && bombTimer > 0.2){
		if (right)
			manager->addBomb1(body->GetPosition().x,body->GetPosition().y,0.5,0.5, pointDirection(body->GetPosition().x,body->GetPosition().x+1,body->GetPosition().y,body->GetPosition().y));
		else
			manager->addBomb1(body->GetPosition().x,body->GetPosition().y,0.5,0.5, pointDirection(body->GetPosition().x,body->GetPosition().x-1,body->GetPosition().y,body->GetPosition().y));
		
		bombTimer = 0;
	} 

	if (bombTimer <= 5)
		bombTimer += time;

	// Damage control.
	if (damageTimer >= 0){
		damageTimer -= time;
	}else{
		damageBool = false;
	}

	if (static_cast<int> (damageTimer*5) % 2 == 1){
		showDamage = true;
	} else {
		showDamage = false;
	}

	if (health <= 0){
		gameStats->addLifes(-1);
		health = 3;
	}
}

void Actor::draw(){
	sf::Vector2i v = visual->getMousePosition();
	animation.sprite.setPosition( x, y);
	if (!showDamage)
		visual->registerDraw(&animation.sprite,2);
}

void Actor::collision(Object * other, int fixtureID){

	// If the actor moves on the ground he has more force than in the air.
	if(fixtureID == 2 && (other->type == ObjectName::BLOCK || other->type == ObjectName::FLOOR)){
		jump = true;
		movementSpeed = 30.0f;
	}
	if (other->type == ObjectName::ENEMY1 && !damageBool ){
		damageBool = true;
		damageTimer = 5;
		showDamage = true;
		health -= 2;
	}

	if (other->type == ObjectName::LADDER){
		body->SetGravityScale(0);
		movementSpeed = 0.5f;
		body->SetAngularDamping(1);
		climbing = true;
		animation.setArea(175,60);
		animation.setFPS(40);
		//animation.start();
		animation.setLoop(true);
	}
}

void Actor::collisionEnd(Object * other, int fixtureID){
	if(other->type == ObjectName::LADDER ){
		body->SetGravityScale(1);
		body->SetAngularDamping(0);
		movementSpeed = 10.0f;
		climbing = false;
	}

	if(fixtureID == 2 && (other->type == ObjectName::BLOCK || other->type == ObjectName::FLOOR)){
		movementSpeed = 10.0f;
	}
}

void Actor::setActorId(int actorId){
	this->actorId = actorId;
}