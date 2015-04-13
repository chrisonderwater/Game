#include "Resource.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "MapLoader.h"
#include "Game.h"
#include <Box2D\Box2D.h>


int main(){
	sf::RenderWindow window(sf::VideoMode(900, 600), "My window");
	window.setFramerateLimit(130); // 130 fps is enough.
	sf::Clock clock;
	sf::Time time;
	Game game(window);


	while (window.isOpen() ){
					sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){
					window.close();
					return 0;
				}

		}
		float elapsed = time.asSeconds();
		time = clock.restart();
		game.update (elapsed);
		game.draw();
		game.render();
	}
	return 0;
}