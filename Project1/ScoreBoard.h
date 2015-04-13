
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Game.h"
#include "MenuItem.h"
#include "INIReader.h"
#include <memory>
#include <list>

struct Score {
	int score;
	std::string name;
};

class ScoreBoard : public MenuItem{
private:
	sf::Font font;
	sf::Sprite background;
	std::vector<sf::Text> scoreText;
	std::list<Score> scores;
	Renderer * visual;
	Game *  game;
	INIReader reader;
public:
	ScoreBoard(Renderer * r, Game * g, sf::Vector2f pos);
	void draw();
	void addScore(std::string n, int s);
	void createText();
	void updateTextPositions();
	void writeScore(std::string s);
	void loadFile(std::string s);
};

#endif