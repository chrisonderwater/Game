#include "GameInfo.h"
#include <cmath>
#include <string>
#include "math.h"
#include "selectColor.h"
#include<stdlib.h>
#include "helperFunctions.h"

// Bind ObjectNames to fileNames.
void GameInfo::setBombFiles(){
	// Bind filenames to bomb ObjectName.
	bombContainer->textures[ObjectName::BOMB1] = "resources/textures/bomb.png";

	// all existing bombs are initialized.
	for (auto i = bombContainer->textures.begin(); i != bombContainer->textures.end(); i++){
		bombContainer->bombs[i->first] = -1;
		// -1: Does not exist. 0: Exists but no bombs currently available.
	}

	resizeBombSprites();
}

void GameInfo::resizeBombSprites(){
	squares.clear();
	bombSprites.clear();
	// Set basic variables.
	sf::Vector2f size = visual->getSize();
	float s = size.y/20;
	sf::Vector2f ss;
	ss.x = s;
	ss.y = s;
	// 1. Initialize available bombs.
	// 2. Create bombsprites and add textures.
	for (auto i = bombContainer->textures.begin(); i != bombContainer->textures.end(); i++){
		
		// Initialize if not initialized:
		if(bombContainer->bombs[i->first] == -1)
			bombContainer->bombs[i->first] = 0;

		sf::Sprite spr;
		spr.setTexture( *visual->getTexture(i->second) ) ;
		int size = visual->getTexture(i->second)->getSize().x;
		spr.setScale(s/size, s/size); 
		bombSprites[i->first] = spr;
		//}
	}

	//Initialize background squares.
	sf::Vector2f pos = visual->getSize();
	pos.y = 0;
	for (auto i = bombSprites.begin(); i != bombSprites.end(); i++){
		sf::RectangleShape square1, square2;
		square1.setSize(ss);
		square1.setFillColor( sf::Color(255,255,255) );
		square2.setSize(ss);
		square2.setFillColor( sf::Color(200,200,200));
		squares.push_back(square1);
		squares.push_back(square2);

	}
}

// Draw bombcontainer (The gameinfo item that shows how many bombs you have.)
void GameInfo::drawBombContainer(){
	sf::Vector2f vp = visual->getViewPosition();
	int j = 0;

	// Draw squares and bombs and text. Readjust positions.bbbbbbbbbbbb
	sf::Vector2f pos = visual->getSize();
	float s = visual->getSize().y/20;
	pos.x += vp.x;
	pos.y = vp.y;
	for (auto i = bombContainer->bombs.begin(); i != bombContainer->bombs.end(); i++, j += 2){
		if ( i->second != -1 ){
			// first block.
			pos.x -= s;
			squares.at(j).setPosition(pos.x, pos.y);
			bombSprites[i->first].setPosition(pos.x, pos.y);

			// Second block.
			pos.y += s;
			squares.at(j+1).setPosition(pos.x, pos.y);
			bombAmount[i->first].setPosition(pos.x+8, pos.y-5);
			bombAmount[i->first].setFont(font);
			bombAmount[i->first].setCharacterSize(s);
			bombAmount[i->first].setString( std::to_string(i->second) );

			visual->registerDraw(&bombSprites[i->first] , 9);
			visual->registerDraw( &bombAmount[i->first], 9);
			visual->registerDraw(&squares.at(j), 8);
			visual->registerDraw(&squares.at(j+1), 8);
			pos.y -= s;
		}
	}
}

GameInfo::GameInfo(Renderer * r, BombContainer * c){
	x = 0;
	y = 0;
	offset = 3;
	visual = r;
	lifes = 0;
	score = 0;
	lifeTexture = visual->getTexture("resources/textures/life.png");
	font.loadFromFile("resources/fonts/kenvector_future.ttf");
	scoreText.setFont(font);
	bombContainer = c;
	setBombFiles();
	sf::Sprite s;
	for(int i=0; i<5;i++){
		keys.push_back(false);
		keySprites.push_back(s);
		keys.at(i) = 0;
		keySprites.at(i).setTexture(*visual->getTexture("resources/textures/key.png"));
		keySprites.at(i).setScale(blocksizeToScale(visual->getBlockSize(), 128), blocksizeToScale(visual->getBlockSize(), 128));
		keySprites.at(i).setColor(selectColor(i));
	}
}
void GameInfo::draw(){
	for (int i = 0; i < lifeSprites.size(); i++){
		visual->registerDraw( &lifeSprites.at(i), 9 );
	}
	for(int i=0; i<keySprites.size();i++){
		if(keys.at(i)){
			keySprites.at(i).setPosition(visual->getViewPosition().x + visual->getSize().x/1.5+100*i,visual->getViewPosition().y+3.0f);
			visual->registerDraw(&keySprites.at(i), 2);
		}
	}
	visual->registerDraw(&scoreText, 9);
	resizeBombSprites();
	drawBombContainer();
}

void GameInfo::addLife(){
	sf::Sprite s;
	lifes++;
	s.setTexture(*lifeTexture);
	lifeSprites.push_back(s);
	float temp = blocksizeToScale(visual->getBlockSize(), 192);
	lifeSprites.back().setScale(temp,temp);
	lifeSprites.back().setPosition( x + 250 + ( (temp*lifeTexture->getSize().x) + offset) * ( lifeSprites.size()-1) ,y);
}

void GameInfo::removeLife(){
	lifes--;
	if (!lifeSprites.empty() )
		lifeSprites.pop_back();
}
void GameInfo::setScore(int amount){
	score = amount;
	std::string text = "Score: ";
	text.append( std::to_string(amount) );
	scoreText.setString(text);
}

void GameInfo::setLifeTexture(sf::Texture * texture){
	lifeTexture = texture;
}

void GameInfo::setPosition(float j, float i){
	x = j;
	y = i;
	float s = blocksizeToScale(visual->getBlockSize(), 192);
	for (int z = 0; z < lifeSprites.size();z++){
		lifeSprites.at(z).setPosition( x + 250 + ( s*lifeTexture->getSize().x + offset) * z, y);
	}
	scoreText.setPosition(x ,y + 1);
}

void GameInfo::setInterfaces(Renderer * r){
	visual = r;
}

void GameInfo::setKey(int key, bool on){
	keys.at(key) = on;
}