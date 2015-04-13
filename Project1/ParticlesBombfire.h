#ifndef PARTICLES_BOMBFIREH
#define PARTICLES_BOMBFIREH
#include "ParticleSystem.h"

class ParticlesBombfire : public ParticleSystem {
	private: 
		sf::Texture * image;
		float growth;
	public:
		explicit ParticlesBombfire( Renderer * r);
		void update (const float time);
		void burst(const int amount);
		void drawExtended();
};

#endif