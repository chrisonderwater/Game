#ifndef PART_BOMB_H
#define PART_BOMB_H

#include "ParticleSystem.h"
#include <memory>

class ParticlesBomb : public ParticleSystem {
	private: 
		sf::Texture * image;
		sf::Sprite black;
		float growth;
	public:
		explicit ParticlesBomb( Renderer * r);
		void update (const float time);
		void burst(const int amount);
		void drawExtended();
};

#endif