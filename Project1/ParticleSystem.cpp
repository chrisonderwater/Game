/* Optimalisaties:
	-Een 2010 computer kon 10.000 sprites afdrukken met SFML. Dan kan een 2013 ipad er wel minstens 1000.
	-Om particles te optimaliseren zullen alle instanties op de stack worden gealloceerd. Deze zullen enkel qua positie 
	  worden gereset. 
*/

#include "ParticleSystem.h"
#include <memory>

void ParticleSystem::setEmitter(const float x, const float y){
	emitter.x = x*visual->getBlockSize();
	emitter.y = y*visual->getBlockSize();
}

void ParticleSystem::setEmitter(const float x, const float y, const float d){
	emitter.x = x*visual->getBlockSize();
	emitter.y = y*visual->getBlockSize();
	direction = d;
}

// Base constructor, will be extended by the child.
ParticleSystem::ParticleSystem(Renderer * r){
	visual = r;
	timer = 0;
}

void ParticleSystem::draw(){
	for (unsigned int i = 0; i < particles.size(); i++){
		visual->registerDraw( &particles.at(i)->sprite, 4);
	}
	drawExtended();
}

void ParticleSystem::setEmitterDirection(float d){
	direction = d;
}

void ParticleSystem::resetTimer(){
	timer = 0.0f;
}

float ParticleSystem::getTimer(){
	return timer;
}

float ParticleSystem::getLifetime(){
	return lifetime;
}