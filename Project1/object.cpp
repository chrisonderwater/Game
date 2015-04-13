#include "ObjectManager.h"
#include "math.h"

/*Laten we nu afspreken: Box2d gaat in meters, sfml in pixels.
  Dus: 1 - 10 meter objecten.
  1 meter object = 96pix
  10 meter object = 960 pix;
  factor 1/68 dus (voor nu ofcrs.)
*/

/*Update de coördinaten x en y en rotation naar de positie van Box2d */
void Object::updateBox2d(){
	/*NOTE coordinaten andersom...*/
	if (body != NULL){
		x = (body->GetPosition().x) * visual->getBlockSize();
		y = (body->GetPosition().y) * visual->getBlockSize();
		rotation = body->GetAngle();
	}
}

void Object::setBody(b2Body * temp){
	body = temp;
}

void Object::setInterfaces(Renderer * render, ObjectManager * mng, GameStats * stats){
	gameStats = stats;
	visual = render;
	manager = mng;
}

void Object::setID(const unsigned int tempID){
	ID = tempID;
}
b2Body * Object::getBody(){
	return body;
}

void Object::impact(const float direction, const float amount, const float damage){
	b2Vec2 point(0,0);
	b2Vec2 vector = directionPoint(0,0,direction,amount);
	body->ApplyLinearImpulse(vector,point,true);
	health -= damage;
}