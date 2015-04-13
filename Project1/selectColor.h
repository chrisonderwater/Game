#include <SFML/Graphics.hpp>

inline sf::Color selectColor(int i){
	switch (i){
	case 0:
		return sf::Color::White;
	case 1:
		return sf::Color::Blue;
	case 2:
		return sf::Color::Black;
	case 3:
		return sf::Color::Red;
	case 4:
		return sf::Color::Green;
	}
	return sf::Color::Green;
}