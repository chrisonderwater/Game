#include "Game.h"
#include "ObjectManager.h"
#include "Menu.h"
#include "INIReader.h"


void Game::update(float time){
	// Alleen de window weet iets over de mouse position.
	gameRender->setMousePosition(*window);
	menuRender->setMousePosition(*window);
	sf::Vector2f pos;
	GameState s = state;
	switch(s){
		case GameState::GAME:
			objectManager->update(time);
			gameRender->update(time);

			// Bridge between gameStats and gameInfo:
			gameInfo->setScore( gameStats->getScore() );

			for (int i = 0; i<gameStats->getLifes();i++){
				gameInfo->addLife();
			}

			for(int i = 0; i > gameStats->getLifes(); i--){
				gameInfo->removeLife();
			}

			for (int i=0;i<5;i++){
				if(gameStats->hasKey(i))
					gameInfo->setKey(i,true);
				else
					gameInfo->setKey(i,false);
			}
			gameInfo->setScore(gameStats->getScore());
			gameStats->resetLifes();

			pos = gameRender->getViewPosition();
			gameInfo->setPosition(static_cast<int>(pos.x), static_cast<int>(pos.y) );

			//Test if the game is won.
			if (gameStats->isGameWon())
				std::cout << "\nGAME IS WON!\n";
			break;
		case GameState::SCOREBOARD:
			scoreboardMenu->update(time);
			break;	

		case GameState::MENU:
			menu->update(time);
			break;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		changeState(GameState::MENU);
	}
}

void Game::render(){
	window->clear();
	GameState s = state;
	switch(s){
	case GameState::GAME:
		gameRender->render(*window);
		break;
	case GameState::MENU:
		menuRender->render(*window);
		break;
	case GameState::SCOREBOARD:
		menuRender->render(*window);
		break;
	}
	window->display();
}

void Game::draw(){
	GameState s = state;
	switch (s){
		case GameState::GAME:
			objectManager->draw();
			gameRender->draw();		// Mostly particles.
			gameInfo->draw();		
			break;
		case GameState::MENU:
			menu->draw();
			break;
		case GameState::SCOREBOARD:
			scoreboardMenu->draw();
			break;
	}
}

void Game::changeState(GameState s){
	state = s;
}

Game::Game(sf::RenderWindow &w){
	state = GameState::SCOREBOARD;
	isGameWon = false;
	window = &w;

	loadSettingsFromFile("settings.ini");

	gameRender = new Renderer;
	gameRender->toggleView();
	BombContainer * container( new BombContainer); // Initialize the container of bombs.
	menuRender = new Renderer;


	gameInfo = new GameInfo(gameRender, container);
	gameStats = new GameStats(container);

	objectManager = new ObjectManager(gameRender);

	// Initialize intro menu.
	menu = new Menu(menuRender, this );
	menu->addPlayButton( (menuRender->getSize().x / 2) / menuRender->getBlockSize() ,1);
	menu->addExitButton( (menuRender->getSize().x / 2) / menuRender->getBlockSize(), 3);

	// Initialize scoreboard menu.
	scoreboardMenu = new Menu(menuRender, this);
	scoreboardMenu->addScoreboard(1,1);


	objectManager->setGameStats(gameStats);

	mapLoader =new MapLoader(objectManager) ;
	
	mapLoader->load("map.txt");
}

void Game::loadSettingsFromFile(std::string fileName){
	INIReader reader;
	reader.read(fileName);
	reader.print();
	settings.width = atoi(reader.getParameterValue("settings","width").c_str());
	settings.height = atoi(reader.getParameterValue("settings","height").c_str());
	sf::Vector2u s(settings.width, settings.height);
	window->setSize( s );
	settings.blockSize = atoi(reader.getParameterValue("settings","blockSize").c_str());
}

void Game::performSettings(){
	gameRender->setSize(settings.width, settings.height);
	gameRender->setBlockSize(settings.blockSize);
	menuRender->setBlockSize(settings.blockSize);
}

void Game::endGame(){
	window->close();
}