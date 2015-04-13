#ifndef GAMEINFO_H
#define GAMEINFO_H
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "BombContainer.h"
// This class shows game information on te screen.

class GameInfo {
private:
	Renderer * visual;

	// Bomb
	std::map<ObjectName, sf::Sprite> bombSprites;
	std::map<ObjectName, sf::Text> bombAmount;
	BombContainer * bombContainer;
	std::vector<sf::RectangleShape> squares;

	// Lifes
	sf::Texture * lifeTexture;
	int lifes;
	std::vector<sf::Sprite> lifeSprites;
	float offset; 

	// Score.
	sf::Text scoreText;
	sf::Font font;
	int score;

	// Position
	int x;
	int y;

	//keys
	std::vector<bool> keys;
	std::vector<sf::Sprite> keySprites;

public:
	GameInfo(Renderer * r, BombContainer * c);
	void setInterfaces(Renderer * r);
	void draw();

	void setBombFiles();
	void drawBombContainer();
	void setPosition(float j, float i);
	void setScore(int amount);
	void addLife();
	void removeLife();
	void setLifeTexture(sf::Texture * texture);
	void resizeBombSprites();
	void setKey(int key, bool on);
};

#endif