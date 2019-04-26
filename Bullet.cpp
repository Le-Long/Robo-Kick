#include "pch.h"
#include "Bullet.h"
#include <math.h>
#include "Window.h"
#include <iostream>
using namespace std;

Bullet::Bullet()
{
}

Bullet::Bullet(Character Gunner, string path)
{
	potentialX = Gunner.x;
	potentialY = Gunner.y;
	this->path = path;
	setPos(potentialX, potentialY);
	vx = 0; vy = 0; 
	velocity = 0;
	denta = 0;
	check_force = 0;
}

void Bullet::move()
{
	vx = velocity * cos(denta);
	vy = velocity * sin(denta) - g * A_MOMENT;
	float road = (velocity*velocity*sin(2 * denta) / g);

	while (!((this->x == Enemy.x && this->y == Enemy.y) || (this->y == Enemy.y - Enemy.height)))
	{
		// Calculate magnitudes of response and velocity vectors
		cout << velocity << endl;
		float velocity = sqrtf(vx*vx + vy*vy);
		denta = atan2(vy, vx);
		x += velocity * cos(denta) * A_MOMENT;
		if (y < Gunner.y + (road / 2))
		{
			y += velocity * sin(denta) * A_MOMENT - g * A_MOMENT*A_MOMENT / 2;
			vy -= g * A_MOMENT;
			cout << "nua dau";
		}
		else
		{
			y -= g * A_MOMENT*A_MOMENT / 2;
			vy += g * A_MOMENT;
			cout << "nua sau";
		}
		//Clear old image
		SDL_RenderClear(gRenderer);

		loadImage("abc.png", 0, 0);
		Gunner.loadObject();
		Enemy.loadObject();
		this->loadObject();
	}

	
	//float fMagResponse = sqrtf(fResponseX*fResponseX + fResponseY * fResponseY);

	// Collision occurred
	if (this->x == Enemy.x && this->y == Enemy.y)
	{
		collision = true;
		//Enemy.getShot(velocity);
	}
	else if (this->y == Enemy.y - Enemy.height)
	{
		collision = true;
		this->collide();
	}
	else if (this->x >= SCREEN_WIDTH)
	{
		collision = false;
		// No collision so update objects position
		x = potentialX;
		y = potentialY;
	}
}

void Bullet::keyEvent(SDL_Event events) 
{
	bool check_get_force = false; // kiem tra lấy được góc chưa
	bool check_get_denta = false; // kien tra lay duoc lực chưa
	

	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_SPACE: // nhập lực
		{
			check_get_denta = true; // do lấy góc trước, nên khi lấy lực thì đã lấy được thành công góc rồi
			check_force = true;
			if (velocity < 3) // lực max = 30
			{
				velocity += 0.1; // dí liệt thì cái này sẽ tăng lên
			}
			else velocity = 3;
			cout << velocity << endl;
			break;
		}
		case SDLK_DOWN:
		{
			if (denta > 0) // denta min =0
			{
				denta -= 1;
			}
			else denta = 0;
		}
		break;
		case SDLK_UP:// nhập góc
		{
			if (denta < 3.14/2 - 0.2) // denta max 
			{
				denta += 0.2;
			}
			else denta = 3.14/2;
			cout << denta << endl;
		}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		cout << 20 << endl;
		if (check_force == true) // nhả từ phím cách 
		{
			check_get_force = true;
			
		}
	}
	if (check_get_force) {
		move();
		cout << 25 << endl;
	}
}

void Bullet::collide()
{
	if (Enemy.x - x < AFFECT_RADIANT && Enemy.x - x > 0)
		Enemy.x += (Enemy.x - x);
	else if (x - Enemy.x < AFFECT_RADIANT && x - Enemy.x > 0)
		Enemy.x -= (Enemy.x - x);
	x = potentialX;
	y = potentialY;
}

Bullet::~Bullet()
{
}
