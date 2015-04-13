#ifndef OBJLADDER_H
#define OBJLADDER_H
#include "Object.h"
#include <vector>

class Ladder : public Object {
private:
	std::vector<sf::Sprite> sprites;
	sf::Sprite sprite;
	sf::RenderTexture newTexture;
	sf::Texture texture;
	float width;
	float height;
public:
	void update(float time);
	void draw();
	void initialize(float width, float height);
	void collision( Object* other, int fixtureID);
};

#endif