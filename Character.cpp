#include "pch.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Character.h"
#include "Window.h"
#include <iostream>

extern SDL_Renderer* gRenderer;

Character::Character()
{
}

Character::Character(string path) : BaseObject()
{
	x_val = 0;
	y_val = 0;
	this->path = path;
	height = 10;
	width = 4;
	HP = 100;
	bool moved = 0;
	texture = loadTexture(path);
}

void Character::move()
{
	if (path == "U-3.png")
		path = "U-5.png";
	else if (path == "U-5.png")
		path = "U-3.png";
	else if (path == "U-2.png")
		path = "U-4.png";
	else if (path == "U-4.png")
		path = "U-2.png";
	texture = loadTexture(path);
	x += x_val;
	if (x < 0 || x + width > SCREEN_WIDTH)
	{
		x -= x_val;
	}
	
}
void Character::keyEvent(SDL_Event mainEvent)
{
	bool face = side;
	if (mainEvent.type == SDL_KEYDOWN)
	{
		switch (mainEvent.key.keysym.sym)
		{
		case SDLK_LEFT:
			x_val = -width / 2;
			face = 1;
			break;
		case SDLK_RIGHT:
			x_val = width / 2;
			face = 0;
			break;
		default:
			x_val = 0;
			break;
		}
		if (face != side) {
			side = face;
			if (path == "U-2.png" || path == "U-4.png") 
				path = "U-3.png";
			else path = "U-2.png";
			texture = loadTexture(path);
		}
		if (moved) {
			x_val = 1;
			moved = 0;
		}
		if (x_val != 0) this->move();
	}
}

void Character::getShot(int velocity)
{
	HP -= velocity;
}

Character::~Character()
{
}
