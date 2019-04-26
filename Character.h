#pragma once
#include "BaseObject.h"
class Character :
	public BaseObject
{
	signed int x_val, y_val;
	int HP;
public:
	Character();
	Character(string path);
	void move();
	void keyEvent(SDL_Event mainEvent);
	//void getShot(int veclocity);
	//void uploadHP();
	~Character();
};

