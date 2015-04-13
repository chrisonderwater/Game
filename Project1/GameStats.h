#ifndef GAMESTATS_H
#define GAMESTATS_H
#include "BombContainer.h"
#include <memory>

// This class manages global game info.

class GameStats {
private:
	unsigned int score;
	unsigned int lifes;
	BombContainer * bombContainer;
	std::vector <bool> locks;
	std::vector <bool> keys;
	int countKeys;
	bool gameIsWon;
public:
	GameStats(BombContainer * b);
	void addScore(unsigned int amount);
	void addLifes(unsigned int amount);
	std::string getBombFileName(ObjectName name);
	int getLifes();
	int getScore();
	void resetLifes();
	void reset();
	void unlock(int i);
	int addLock();
	int addKey();
	void keyObtained(int i);
	bool hasKey(int i);
	void setGameWon();
	bool isGameWon();
};

#endif