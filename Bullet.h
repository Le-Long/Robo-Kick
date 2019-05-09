#pragma once
#include "BaseObject.h"
#include "Character.h"

const float AFFECT_RADIANT = 40;
const float A_MOMENT = 0.4;
const int g = 1;
//const int RAD = 30;

extern SDL_Texture* gTexture;
extern SDL_Renderer* gRenderer;

class Bullet :
	public BaseObject
{
public:
	bool check_force; // check nhấn space hay lên xuống
	Character Enemy, Gunner;
	float velocity, denta, vx, vy,
		potentialX, potentialY,
		point_x, point_y;
	int sign;
	bool died = 0;
	Bullet();
	Bullet(Character Gunner, string path);
	void move();
	void keyEvent(SDL_Event events);
	void collide();
	~Bullet();
};

