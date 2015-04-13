#include "ParticlesBomb.h"
#include "math.h"
#include <cmath>
#include <Box2D\Box2D.h>

// Hoe worden ParticlesBomb geupdate ?
void ParticlesBomb::update(const float time){
	// update background image:
	growth += time*1.5;
	black.setScale(growth*blocksizeToScale(visual->getBlockSize(),96), growth*blocksizeToScale(visual->getBlockSize(),96));
	sf::Color c = sf::Color(255,255,255, 255-timer*300);
	black.setColor(c);

	// update particles.
	for (int i = 0; i < particles.size();i++){
		//Here information is loaded.
		float x = particles.at(i)->sprite.getPosition().x;
		float y = particles.at(i)->sprite.getPosition().y;
		float direction = particles.at(i)->direction;
		float velocity = particles.at(i)->velocity;

		// From here : Adjustments are made.
		b2Vec2 position = directionPoint( x, y, direction, time*velocity );
		if (particles.at(i)->velocity > 0)
			particles.at(i)->velocity -= time * 0.15; //Rem particles een beetje af.
		particles.at(i)->sprite.rotate(time*2000);
		particles.at(i)->sprite.setPosition( position.x, position.y );
		particles.at(i)->sprite.setColor(c);
		particles.at(i)->direction += time * 10;
	}
	timer += time;
}

// Door dit trucje overschrijft de baseclass constructor en voegt hier evt. nog extra functionaliteit aan toe.
// Extra functionaliteit: Inladen van de benodigde plaatjes.
ParticlesBomb::ParticlesBomb( Renderer * r): ParticleSystem(r){
	image = visual->getTexture("resources/textures/particleBomb1.png" );
	lifetime = 0.8;

	// Initiate background image.
	black.setTexture(*visual->getTexture("resources/textures/particleBomb1black.png") );
	sf::Vector2u s = visual->getTexture("resources/textures/particleBomb1black.png")->getSize();
	black.setOrigin(s.x/2, s.y/2);
	black.setScale(growth*blocksizeToScale(visual->getBlockSize(),96), growth*blocksizeToScale(visual->getBlockSize(),96));
}

// Burst een groep particles.
// Eigenlijk doet het niets anders dan een klein groepje vertices in de vertexarray plaatsen.
void ParticlesBomb::burst(const int amount){
	// Initialize background image.
	growth = 0;
	black.setPosition(emitter.x, emitter.y);
	for (unsigned int i = 0; i < amount; i++){
		// Create new particle.
		Particle * particle = new Particle;
		particle->sprite.setTexture(*image);
		particle->sprite.setScale(blocksizeToScale(visual->getBlockSize(),96), blocksizeToScale(visual->getBlockSize(),96));
		particle->sprite.setOrigin(image->getSize().x/2,image->getSize().y/2);
		particle->sprite.setPosition(emitter.x, emitter.y);
		particle->sprite.rotate(rand()%360);
		particles.push_back(particle);	
		
		particle->velocity = 200.2;
		particle->direction = i*(360/amount);
		particle->lifetime = 5;
	}
}

void ParticlesBomb::drawExtended(){
	visual->registerDraw(&black, 4);
}
