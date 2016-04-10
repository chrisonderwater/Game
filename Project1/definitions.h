#ifndef DEFINITIONS_H
#define DEFINITIONS_H
// global definitions for the game.

namespace def{
enum class GAME_TYPE{
	CLIENT,
	SERVER,
	HYBRID
};
}

const def::GAME_TYPE GAME_TYPE = def::GAME_TYPE::SERVER;

const int MAX_AMOUNT_OBJECTS = 2000;



#endif