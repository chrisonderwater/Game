// Game class, manages game states and owns all the game specific objects.
// For pausing, changing to menu, slowing down, scaling, and other game management functionality.
#ifndef GAME_H
#define GAME_H

/* WIP het maken van ee scorebord.*/

#include "ObjectManager.h"
#include "Renderer.h"
#include "MapLoader.h"
#include "Resource.h"
#include "Settings.h"
#include "GameStats.h"
#include "GameInfo.h"
#include <string>

class Menu;
	
enum class GameState{
	MENU,
	GAME,
	PAUSE,
	SCOREBOARD,
	GAMEOVER
};

class Game {
	private:
		sf::RenderWindow *  window;
		Renderer *  gameRender;
		Renderer *  menuRender;
		ObjectManager * objectManager;
		Menu * menu;
		Menu * scoreboardMenu;
		MapLoader * mapLoader;
		GameState state;
		Settings settings;
		GameInfo * gameInfo;
		GameStats * gameStats;
		bool isGameWon;

	public:
		Game(sf::RenderWindow &w);
		void endGame();
		void loadSettingsFromFile(std::string fileName);
		void performSettings();
		void update(float time);
		void draw();
		void render();
		void changeState(GameState s);
		void resizeRenderers(float width, float height);
};
#endif