#include "Floor.h"
#include "math.h"

void Floor::initialize(float width, float height){
	type = ObjectName::FLOOR;
	rectangle.setSize(sf::Vector2f(width*visual->getBlockSize(), height*visual->getBlockSize() ) );
	rectangle.setOrigin((width*visual->getBlockSize())/2, (height*visual->getBlockSize())/2 );
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setFillColor(sf::Color::White);

	//Create Box2D shape. (Seems like something to handle for object.)
	b2PolygonShape groundBox;
	groundBox.SetAsBox(width/2, height/2);//Note: Both multiplied by 2. (100*20)
	//And, of course: Bind the *fixture to the body. (* -- this is a shortcut, not a fixture but a shape.)
	body->CreateFixture(&groundBox, 0.0f);
}

void Floor::update(float time){
}

void Floor::draw(){
	rectangle.setPosition(x,y);
	rectangle.setRotation(radiansToDegrees(rotation));
	visual->registerDraw(&rectangle,0);
}

void Floor::impact(const float direction, const float amount, const float damage){
	// The floor has no impact.
}