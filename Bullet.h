#pragma once
#include "BaseObject.h"
#include "Character.h"

const int AFFECT_RADIANT = 50;
const float A_MOMENT = 0.1;
const int g = 2;

extern SDL_Renderer* gRenderer;

class Bullet :
	public BaseObject
{
public:
	bool check_force; // check nhấn space hay lên xuống
	Character Enemy, Gunner;
	float velocity, denta, vx, vy,  
		potentialX, potentialY;
	bool collision = 0;
	Bullet();
	Bullet(Character Gunner, string path);
	void move();
	void keyEvent(SDL_Event events);
	void collide();
	~Bullet();
};

