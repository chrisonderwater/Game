/*
This is a simple interface that provides functionality for abstraction of drawing methods.
*/

#ifndef REN_H
#define REN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Resource.h"
#include "LightsManager.h"

// Belangrijk! In de .h een simpele definitie, in de .cpp de gehele .h includen!
class ParticleSystem;

class Renderer{
	private:
		Resource<sf::Texture> * resources;
		std::vector< ParticleSystem* > particleSystems;
		std::vector < std::vector< sf::Drawable* > > drawBuffers;
		std::vector<Light> * lights;

		sf::Vector2i mouseCoordinates;
		bool mouseIsPressed;
		sf::View view;
		sf::Sprite background;

		float backgroundX,backgroundY;
		float x;
		float y;
		int blockSize;
		float width;
		float height;
		bool isView;
	public:
		Renderer();
		~Renderer();

		//Rendering needs window, mouse needs window too.
		sf::Vector2i getMousePosition();
		bool getMousePressed();
		void setMousePosition(sf::RenderWindow &window);
		void render(sf::RenderWindow &window);       //Render all drawables to window.
		void registerDraw( sf::Drawable * drawable, const unsigned int priority);  //Register a drawable to draw.
		sf::Texture * getTexture(std::string name);  //Obtain a sprite-pointer from resourcemanager.
		void setViewCenter(float x, float y);
		float getBlockSize();
		sf::Vector2f getViewPosition();
		void setBackground(std::string fileName);
		// Particle related functionality.
		void addParticleSystem( ParticleSystem * p);
		void update (const float time);
		void draw();
		void toggleView();
		//Settings
		void setSize(unsigned int w, unsigned int h);
		void setBlockSize(unsigned int size);
		int addLight(Light &light);
		void removeLight(int id);
		Light * getLight(int id);
		std::vector<Light> * getLights();
		sf::Vector2f getSize();
};

#endif