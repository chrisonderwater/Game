#include "GameStats.h"

std::string GameStats::getBombFileName(ObjectName name){
	return bombContainer->textures[name];
}

GameStats::GameStats(BombContainer * b){
	bombContainer = b;
	score = 0;
	lifes = 0;
	gameIsWon = false;
	countKeys = 0;
}
void GameStats::addScore(unsigned int amount){
	score += amount;
}

int GameStats::getScore(){
	return score;
}

void GameStats::addLifes(unsigned int amount){
	lifes += amount;
}

int GameStats::getLifes(){
	return lifes;
}

void GameStats::resetLifes(){
	lifes = 0;
	//score = 0;
}

void GameStats::reset(){
	resetLifes();
	locks.clear();
	score = 0;
	//bombContainer->bombs
	//score = 0;
}

void GameStats::unlock(int i){
	if (i < locks.size() ){
		if(keys.at(i) == true) // Als hij de sleutel heeft:
			locks.at(i) = true;
	}

	for (i = 0; i < locks.size(); i++){
		if(locks.at(i) == false)
			return;	// Exit als er nog een gesloten slot is.
	}
	setGameWon();
}

int GameStats::addLock(){
	keys.push_back(false);
	locks.push_back(false);
	return locks.size() - 1;
}

void GameStats::setGameWon(){
	gameIsWon = true;
}

bool GameStats::isGameWon(){
	return gameIsWon;
}

void GameStats::keyObtained(int i){
	keys.at(i) = true;
}

bool GameStats::hasKey(int i){
	if (i < (keys.size()))
		return keys.at(i);
	else
		return false;
}

int GameStats::addKey(){
	countKeys++;
	return countKeys - 1;
}