#include "pch.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Character.h"
#include "Window.h"

extern SDL_Renderer* gRenderer;

Character::Character()
{
	x_val = 0;
	y_val = 0;
	height = 10;
	width = 4;
	HP = 20;
}

Character::Character(string path) : BaseObject(path)
{
	x_val = 0;
	y_val = 0;
	this->path = path;
	height = 10;
	width = 4;
}

void Character::move()
{
	x += x_val;
	if (x < 0 || x + width > SCREEN_WIDTH)
	{
		x -= x_val;
	}
	
}
void Character::keyEvent(SDL_Event mainEvent)
{
	if (mainEvent.type == SDL_KEYDOWN)
	{
		switch (mainEvent.key.keysym.sym)
		{
		case SDLK_LEFT:
			x_val = -width / 2;
			break;
		case SDLK_RIGHT:
			x_val = width / 2;
			break;
		default:
			x_val = 0;
			break;
		}
		if (x_val != 0) this->move();
	}
}


Character::~Character()
{
}
