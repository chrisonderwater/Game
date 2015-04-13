# include "ScoreBoard.h"
#include "math.h"
#include <algorithm>
#include "helperFunctions.h"

/*
Better make this portable...
Never want to go through this again xD
( Modern implementations make use of Steam, android or Apple cloud based score boards.)
*/
bool compare(Score first, Score second){
	return first.score < second.score;
}

// Create new text vector according to scores list.
void ScoreBoard::createText(){
	scoreText.clear();
	int count = 0;
	for(auto i = scores.begin(); i != scores.end(); i++, count++){
		// Initialize text.
		sf::Text name, score;
		name.setFont(font);
		name.setColor(sf::Color::Black);
		name.setCharacterSize( visual->getSize().x/30 ); 
		score.setFont(font);
		score.setColor(sf::Color::Black);
		score.setCharacterSize( visual->getSize().x/30 ); 
		// Note: Text must be scaled if there is a higher block size!
		name.setString(i->name);
		score.setString(std::to_string(i->score) );
		name.setPosition( visual->getSize().x/10, visual->getSize().x/15 * count);
		score.setPosition( (visual->getSize().x/10) *3, visual->getSize().x/15 * count);
		scoreText.push_back(name);
		scoreText.push_back(score);
	}
}

ScoreBoard::ScoreBoard(Renderer * r, Game * g, sf::Vector2f pos){

	visual = r;
	game = g;

	position.x = pos.x;
	position.y = pos.y;
	font.loadFromFile("resources/fonts/kenvector_future.ttf");
	background.setTexture( *visual->getTexture("resources/textures/backgroundScoreboard.png") );
	float newWidth = blocksizeToScale(   visual->getSize().x, 1366 );
	float newHeight = blocksizeToScale( visual->getSize().y, 1040);
	background.setScale( newWidth, newHeight );
	
	loadFile("scores.txt");
	addScore("lol", 11);
	addScore("Kees", 1000);
	addScore("Jaap", 10);
	createText();
	writeScore("scores_nieuw.txt");
}

// Add a score to the scores list. Sorted!
void ScoreBoard::addScore(std::string n, int s){
	Score temp;
	temp.name = n;
	temp.score = s;

	// List. Left side lowest, right side highest. Sorted ascending
	for ( auto i = scores.begin(); i != scores.end(); i++){
		if (temp.score > i->score){
			scores.insert(i,temp);
			// This does not belong to the core tasks I think.
			// reader.writeParameterValue(n,"score", std::to_string(s) );
			// createText();
			return;
		}
	}
	// If it's highest, insert on the right side.
	scores.push_back(temp);

	//  This does not belong to the core tasks I think.
	//reader.writeParameterValue(n,"score", std::to_string(s) );
	//createText();
}

// Draw scoreboard to the renderer.
void ScoreBoard::draw(){
	visual->registerDraw(&background,0);
	for(int i=0; i < scoreText.size() ; i++){
		visual->registerDraw(&scoreText.at(i), 2 );
	}
}

// Algorithm that readjusts text positions to current scores.
void ScoreBoard::updateTextPositions(){
	for (int i= 0; i < scoreText.size(); i++ ){
		if (isEven(i) )
			scoreText.at(i).setPosition(visual->getSize().x / 10, visual->getSize().x/15 * i);
		else
			scoreText.at(i).setPosition((visual->getSize().x / 10) * 3, visual->getSize().x/15 * (i-1) );
	}

}

// Write scores to a file
void ScoreBoard::writeScore(std::string s){
	INIReader r;
	// Write current score to a new INI file.
	for ( auto i = scores.begin(); i != scores.end(); i++){
		r.writeParameterValue(i->name, "score", std::to_string(i->score) );
	}
	r.write(s);
}

// Load a INI file.
void ScoreBoard::loadFile(std::string s){
	reader.read(s);
	for (int i = 0; i < reader.elements.key.size(); i++){
		// Initialize score element.
		addScore(reader.elements.key.at(i), std::stoi(reader.getParameterValue(reader.elements.key.at(i), "score")) );
	}
}