/*Renderer.
Abstraction layer between the resource manager, the renderwindow and objects.
Adds drawable objects and sounds to a queue and renders the whole package.
Features:
-Allows a depth parameter while drawing.
-Manages the background.
-Everything render related comes together in one class (resources, drawables, sprites, sounds)
-Every render environment has its own resources. (e.g. menu, game, map)
-Enforces views (view only a part of the entire rendered screen.)
-Enforces portable resolutions. (Box2d's coordinate system is a relative one, SFML has an absolute one,
			        using a BlockSize variable the system decides how many pixels one Box2D metric is.)
-Is used to obtain the mouse position (because mouse position is a parameter of the screen).
*/
#include "Renderer.h"
#include "ParticleSystem.h"

//Constructor.
Renderer::Renderer(){
	backgroundX = 0;
	backgroundY = 0;

	blockSize = 64;	
	width = 1280;
	height = 900;
	isView = false;

	resources = new Resource<sf::Texture>;
	view.setSize(sf::Vector2f(width, height));
	mouseIsPressed = false;
	drawBuffers.resize(10);

	lights = new std::vector<Light>;
}

Renderer::~Renderer(){
	delete lights;
	delete resources;

}

//Render(). Empty draw container and print them FIFO.
void Renderer::render(sf::RenderWindow &window){
	if (isView)
		window.setView(view);
	else
		window.setView(viewMenu );

	// Draw the background.
	window.draw(background);
	for (int i = 0; i < drawBuffers.size(); i++){
		while(!drawBuffers.at(i).empty()){
			if(drawBuffers.at(i).back() != NULL){
				window.draw( *(drawBuffers.at(i).back() ) );
				drawBuffers.at(i).pop_back();
			}
		}
	}

	// Resize the Renderer to the window size!
	width = window.getSize().x;
	height = window.getSize().y;
	view.setSize(sf::Vector2f(width, height));
	viewMenu.setSize(sf::Vector2f(width, height));
	viewMenu.setCenter(sf::Vector2f(width/2,height/2));
}

//Zet de af te drukken drawable in de lijst. Priority is: 0 - 9. 9 Is top
void Renderer::registerDraw(sf::Drawable * drawable, const unsigned int priority){
	drawBuffers.at(priority).push_back(drawable);
}

//Interface function. Returns a resource from resourceloader.
sf::Texture * Renderer::getTexture(std::string name){
	return resources->get(name);
}

sf::Vector2i Renderer::getMousePosition(){
	return mouseCoordinates;	
}

void Renderer::setMousePosition(sf::RenderWindow &window){
	mouseCoordinates = sf::Mouse::getPosition(window);
	mouseIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Renderer::setViewCenter(float x, float y){
	sf::Vector2f position = view.getCenter();
	float dx = position.x;
	float dy = position.y;
	view.setCenter(sf::Vector2f(x,y));
	dx = x - dx;
	dy = y - dy;
	if (  (dx > -2 && dx < 2) && (dy > -2 && dy < 2) ){     // <- prevents from falling out of the map!
		backgroundX -= dx/20;								//rate movement karakter vs. background
		backgroundY -= dy/20;
	}
	background.setPosition(x+backgroundX,y+backgroundY);
}

float Renderer::getBlockSize(){
	return blockSize;
}

void Renderer::setBackground(std::string fileName){
	background.setTexture(*resources->get(fileName));
	sf::Vector2u size = resources->get(fileName)->getSize();
	background.setOrigin(size.x/2, size.y/2);				//Verplaats x=0,y=0 naar het midden.
}

void Renderer::addParticleSystem(ParticleSystem * p){
	particleSystems.push_back(p);
}

//Update function, mostly for updating particle systems.
void Renderer::update(const float time){
	for (int i = 0;i<particleSystems.size(); i++){
		particleSystems.at(i)->update(time);
		if (particleSystems.at(i)->getTimer() > particleSystems.at(i)->getLifetime()){
			std::swap(particleSystems.at(i), particleSystems.back() );
			particleSystems.pop_back();
		}
	}
}

void Renderer::draw(){
	for (int i=0;i<particleSystems.size();i++){
		particleSystems.at(i)->draw();
	}
}

void Renderer::setSize(unsigned int w, unsigned int h){
	width = w;
	height = h;
	sf::Vector2f temp;
	temp.x = w;
	temp.y = h;
	view.setSize(temp);
}
void Renderer::setBlockSize(unsigned int size){
	blockSize = size;
}

sf::Vector2f Renderer::getViewPosition(){
	sf::Vector2f pos = view.getCenter();
	sf::Vector2f size = view.getSize();
	//Return position from left top.
	pos.x -= size.x/2;
	pos.y -= size.y/2;
	return pos;
}

void Renderer::toggleView(){
	if(isView)
			isView = false;
		else
			isView = true;
}

bool Renderer::getMousePressed(){
	return mouseIsPressed;
}

sf::Vector2f Renderer::getSize(){
	sf::Vector2f s;
	s.x = width;
	s.y = height;
	return s;
}

int Renderer::addLight(Light & light){
	lights->push_back(light);
	lights->back().setID( lights->size()-1 );
	return lights->size()-1;
}

void Renderer::removeLight(int id){
	lights->back().setID( id );
	std::swap(lights->at(id), lights->back() );
	lights->pop_back();
}

Light * Renderer::getLight(int id){
	return &lights->at(id);
}

std::vector<Light> * Renderer::getLights(){
	return lights;
}