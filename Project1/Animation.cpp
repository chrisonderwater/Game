#include "Animation.h"

Animation::Animation(){
	offset = 0;
	size = 0;
	loop = true;
	position = 0;
	fps = 60;
	scaleWidth = 1.0f;
	scaleHeight = 1.0f;
	isMoving = false;
}

void Animation::setTexture(sf::Texture * texture){
	this->texture = texture;
	sprite.setTexture(*this->texture);
}

// State machine implementation for quickly importing XML file.
// Quick, dirty but certainly effective.
void Animation::getPositionFile(std::string fileName){
	std::ifstream file(fileName);
	std::string temp = "";
	int counter = 0;
	int state = 4;
	ListItem tempItem;
	char c = file.get();
	//states: 0 = x, 1 = y, 2 = width, 3 = height, 4 = reading.
	while(!file.eof() ){
		if(temp.find("x=\"") != std::string::npos){
			state = 0;
			temp = "";
		} else if(temp.find("y=\"") != std::string::npos){
			state = 1;
			temp = "";
		} else if(temp.find("width=\"") != std::string::npos){
			state = 2;
			temp = "";
		} else if(temp.find("height=\"") != std::string::npos){
			state = 3;
			temp = "";
		}else if ( (temp.find("\"") != std::string::npos) && state != 4){
			switch(state){
				case 0:
					tempItem.x = std::atoi(temp.c_str());
					temp = "";
					break;
				case 1:
					tempItem.y = std::atoi(temp.c_str());
					temp = "";
					break;
				case 2:
					tempItem.width = std::atoi(temp.c_str());
					temp = "";
					break;
				case 3:
					tempItem.height = std::atoi(temp.c_str());
					temp = "";
					animationList.push_back(tempItem);
					state = 4;
					break;
			}
		}
		temp.push_back(c);
		c = file.get();
	}
	file.close();
}

void Animation::setArea(int offset, int size){
	this->offset = offset;
	this->size = size;
}

void Animation::update(float time){
	if (position >= size && loop == true )
		position = 0;
	else if (position >= size && loop == false)
		position = size;
	int temp = static_cast<int>(position);
	sf::IntRect rect;
	rect.left = animationList.at(offset+temp).x;
	rect.top = animationList.at(offset+temp).y;
	rect.width = animationList.at(offset+temp).width;
	rect.height = animationList.at(offset+temp).height;
	sprite.setTextureRect(rect);
	sprite.setOrigin(  rect.width/2, rect.height/2);
	sprite.setScale(scaleWidth,scaleHeight);

	// There are fps frames in a second.
	if (isMoving)
		position += time * fps;
}

void Animation::setScale(float scaleW, float scaleH){
	scaleWidth = scaleW;
	scaleHeight = scaleH;
}

void Animation::start(){
	isMoving = true;
}

void Animation::stop(){
	isMoving = false;
}

void Animation::setFPS(int f){
	fps = f;
}

void Animation::setLoop(bool l){
	loop = l;
}

void Animation::rewind(){
	position = 0;
}