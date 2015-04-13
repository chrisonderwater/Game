#ifndef ANIMATIO_H
#define ANIMATIO_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>

struct ListItem{
	int x;
	int y;
	int width;
	int height;
};

class Animation {
	private:
		sf::Texture * texture;
		std::vector<ListItem> animationList;
		bool loop;
		int offset;
		int size;
		float position;
		int fps;
		float scaleWidth;
		float scaleHeight;
		bool isMoving;
	public:
		sf::Sprite sprite;
		Animation();
		void setTexture (sf::Texture * texture);
		void getPositionFile(std::string fileName);
		void setArea(int offset, int size);
		void update(float time);
		void setFPS(int f);
		void setScale(float scaleW, float scaleH);
		void start();
		void stop();
		void setLoop(bool l);
		void rewind();
};



#endif