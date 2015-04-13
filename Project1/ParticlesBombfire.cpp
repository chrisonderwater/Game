#include "ParticlesBombfire.h"
#include "math.h"

ParticlesBombfire::ParticlesBombfire(Renderer * r) : ParticleSystem(r){
	float alpha = 1.0f;
	lifetime = 5.0f;
	image = visual->getTexture("resources/textures/ster.png");
}


void ParticlesBombfire::update(const float time){
	sf::Vector2f tempPosition;
	b2Vec2 positionVector;
	for (int i = 0; i < particles.size(); i++){
		if (particles.at(i) != NULL){

			// Set particle position at bomb burning hole.
			positionVector = directionPoint(0,0,direction, 0.25f);
			positionVector.x *= visual->getBlockSize();
			positionVector.y *= visual->getBlockSize();
			tempPosition.x = emitter.x + positionVector.x;
			tempPosition.y = emitter.y + positionVector.y;
			particles.at(i)->sprite.setPosition(tempPosition.x, tempPosition.y);
			particles.at(i)->direction += particles.at(i)->rotationSpeed*time*0.01;
			particles.at(i)->sprite.setRotation( radiansToDegrees(particles.at(i)->direction) );
			// Since it's an array of pointers the speed penalty of this quickfix is neglectable.
			if(particles.at(i)->timer > particles.at(i)->lifetime){
				delete particles.at(i);
				particles.at(i) = NULL;
			}
		}
	}

	timer += time;
}

void ParticlesBombfire::burst(const int amount){
	for (int i=0; i < amount;i++){
		Particle * temp = new Particle;
		temp->sprite.setTexture(*image);
		temp->sprite.setOrigin(image->getSize().x/2, image->getSize().y/2);
		temp->sprite.setPosition(emitter.x, emitter.y);
		temp->sprite.setScale(blocksizeToScale(visual->getBlockSize(),96), blocksizeToScale(visual->getBlockSize(),96));
		temp->direction = direction - 5 + (rand()%10);
		temp->velocity = 1.0f / static_cast<float>(rand()%50);
		temp->lifetime = 1.0f;
		temp->rotationSpeed = 180 / static_cast<float>(rand()%10);
		temp->timer = 0.0f;
		particles.push_back(temp);
	}
}

void ParticlesBombfire::drawExtended(){

}