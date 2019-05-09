#pragma once
#include "BaseObject.h"
class Character :
	public BaseObject
{
 public:
	int HP, x_val, y_val;
	bool side;
	Character();
	Character(string path);
	void move();
	void keyEvent(SDL_Event mainEvent);
	void getShot(int velocity);
	//void uploadHP();
	~Character();
};

