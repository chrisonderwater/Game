#ifndef SETTINGS_H
#define SETTINGS_H
enum class RenderQuality{
	LOW,
	MEDIUM,
	HIGH
};

struct Settings{
	bool fullScreen;
	unsigned int width;
	unsigned int height;
	unsigned int blockSize;
	RenderQuality renderQuality;
};
#endif