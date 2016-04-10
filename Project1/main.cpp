#include "Resource.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "MapLoader.h"
#include "Game.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <thread>

void updateThread(Game * game, sf::Window * window, float elapsed){
	window->setActive(false);
	game->update(elapsed);
}

int main(){
	sf::RenderWindow window(sf::VideoMode(900, 600), "My window");
	window.setFramerateLimit(60); // 130 fps is enough.
	sf::Clock clock;
	sf::Time time;
	Game game(window);
	float lastTime = 0;

	while (window.isOpen() ){
					sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){
					window.close();
					return 0;
				}

				if(event.type == sf::Event::Resized){
					game.resizeRenderers( event.size.width, event.size.height);
				}

		}
		float elapsed = time.asSeconds();
		if( (1.0f / elapsed) < 20 ){
			std::cout << "FPS below 20" << std::endl;
		}
		time = clock.restart();
		game.update(elapsed);
		game.draw();
		game.render();
	}
	return 0;
}