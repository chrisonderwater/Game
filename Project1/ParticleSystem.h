/* 
Dit is een vrij eenvoudig en flexibel particle systeem dat gebruik maakt van sprites.
Het is heel eenvoudig te programmeren doordat een particle een sprite is met een aantal extra attributen.
Iedere particle kan dus zijn huidige positie of snelheid ophalen. 
Dit is niet efficient bij klassieke particle systems (pixels of primitieve vormen) 
Als veel gebruik gemaakt wordt van sprite manipulatie functies en het aantal sprites relatief laag gehouden wordt
is het systeem wel degelijk efficient.

Een heel erg efficient particle-system zou gemaakt moeten worden met vertexArrays.
Dit brengt echter veel onduidelijke code met zich mee en ook functionele beperkingen.
Er is gekozen om het met sprites te doen en hiervoor in ruil iets minder te drawen.
Waarschijnlijk is C++ i.c.m. SFML alsnog erg efficient, zelfs op een tablet.*/
#ifndef PARTS_H
#define PARTS_H
#include <SFML/Graphics.hpp>
#include "Renderer.h"

// A sprite with some particle specific attributes.
struct Particle{
	sf::Sprite sprite;
    float velocity;
    float lifetime;
	float timer;
	float direction;
	float rotationSpeed;
};

class ParticleSystem {
protected:
	std::vector< Particle * > particles;
    float lifetime;
	float direction;
	float timer;
    sf::Vector2f emitter;
	Renderer * visual;
public:
	ParticleSystem( Renderer * r);
	virtual void update(const float time) = 0;
	void draw();
	virtual void drawExtended(){};
	virtual void burst(const int amount)=0;

	// Coordinates are given in the b2D coordinate system!
	void setEmitter(const float x, const float y);
	void setEmitter(const float x, const float y, const float d);
	void setEmitterDirection (float d);
	void resetTimer();

	float getTimer();
	float getLifetime();
		// Burst is een functie die de emitter een burst laat doen.
};
#endif