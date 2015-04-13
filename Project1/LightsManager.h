
#ifndef LIGHTSMANAGER_H
#define LIGHTSMANAGER_H

#include "Light.h"
#include <Box2D\Box2D.h>
#include <vector>

class Renderer; 

class LightsManager {
	private:
		Renderer * visual;
		b2World  * world;
		std::vector<Light> * lights;
		sf::VertexArray vertices;

	public:
		LightsManager(b2World * world, Renderer * visual);
		void setLights(std::vector<Light> * lights);
		void update();
		void draw();
};


#endif