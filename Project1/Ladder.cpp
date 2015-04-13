#include "Ladder.h"
#include "math.h"

void Ladder::update(float time){

}
void Ladder::draw(){
	sprite.setPosition(x,y);
	sprite.setRotation( radiansToDegrees(body->GetAngle()));
	visual->registerDraw(&sprite,1 );
}
void Ladder::initialize(float width, float height){
	type = ObjectName::LADDER;
	health = 5.0f;
	sf::Texture * t = visual->getTexture("resources/textures/ladder.png");
	float s = blocksizeToScale(visual->getBlockSize(), 339);
	this->width = width;
	this->height = height;

	int h = static_cast<int>(height);
	newTexture.create(visual->getBlockSize(), visual->getBlockSize()*h);
	for (int i = 0; i < h; i++){
		sf::Sprite temp;
		temp.setTexture(*t);
		temp.setScale(s,s);
		sprites.push_back(temp);
	}
	
	for (int i = 0; i < h; i++){
		sprites.at(i).setPosition(0, i * visual->getBlockSize() );
		newTexture.draw( sprites.at(i));
	}
	newTexture.display();
	sprite.setTexture( newTexture.getTexture() );
	sprite.setOrigin(newTexture.getTexture().getSize().x/2,  newTexture.getTexture().getSize().y/2);
	

	b2PolygonShape box;

	// Try to make Box2D size as an inference to image size.
	box.SetAsBox( width/2 , height/2 );
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 2;
	fixture.friction = 2;
	body->CreateFixture(&fixture);


}
void Ladder::collision( Object* other, int fixtureID){

}