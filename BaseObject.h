#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

class BaseObject
{
public:
	string path;
	float x,y;
	SDL_Texture* texture = NULL;
	int height, width;

	BaseObject();
	BaseObject(string pathSet);
	void setPos(int xSet, int ySet);
	void loadObject();
	int getWidth();
	int getHeight();
	void virtual move() = 0;
	void virtual keyEvent(SDL_Event mainEvent) = 0;
	~BaseObject();
};

