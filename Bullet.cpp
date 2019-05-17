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
	height = Gunner.height;
	width = Gunner.width;
	this->path = path;
	texture = loadTexture(path);
	setPos(potentialX, potentialY);
	vx = 0; vy = 0; 
	velocity = 0;
	denta = 0;
	check_force = 0;
}

void Bullet::move()
{
	float denta2 = denta * 3.14 / 180;
	
	vx = sign * velocity * cos(denta2); // v theo x
	vy = -velocity * sin(denta2); // v theo y
	
	while (!((this->x >= SCREEN_WIDTH) || (this->y <= 0) || (this->x <= 0) || (this->y >= Enemy->y + Enemy->height)))
	{

		x += vx * A_MOMENT;
		vy += g * A_MOMENT / 2.0;
		y += vy * A_MOMENT;
		velocity = sqrt(vx*vx + vy * vy);

		SDL_RenderClear(gRenderer);
		loadImage(gTexture, 0, 0);
		loadObject();
		loadPlayer(Gunner, Enemy);
		
	}
	
	// Collision occurred
	if (((x + width) >= Enemy->x) && (x <= (Enemy->x + width))
		&& (y + height <= Enemy->y + AFFECT_RADIANT) && (y + height >= Enemy->y))
	{
		died = true;
		Enemy->getShot(velocity * 2);
		collide();
	}

	if (this->y + height >= Enemy->y + Enemy->height)
	{
		died = true;
		this->collide();
	}
	else if ((this->x >= SCREEN_WIDTH) || (this->y <= 0) || (this->x <= 0))
	{
		died = true;
		// No collision so update objects position
		x = potentialX;
		y = potentialY;
		velocity = 0;
		check_force = 0;

		loadPlayer(Gunner, Enemy);
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
			if (velocity < 30) // lực max = 30
			{
				velocity += 1; // dí liệt thì cái này sẽ tăng lên
			}
			else velocity = 30;
			cout << velocity << endl;
			break;
		}
		case SDLK_DOWN:
		{
			if (denta > 0) // denta min =0
			{
				denta -= 10;
				point_x += sign * 0.9;
				point_y += 2.6;
			}
			else denta = 0;
			cout << denta << endl;
		}
		break;
		case SDLK_UP:// nhập góc
		{
			if (denta < 90) // denta max 
			{
				denta += 10;
				point_x -= sign * 0.9;
				point_y -= 2.6;
			}
			else denta = 90;
			cout << denta << endl;
		}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		if (check_force == true) // nhả từ phím cách 
		{
			check_get_force = true;
		}
	}
	if (check_get_force) {
		move();
		
	}
}

void Bullet::collide()
{
	SDL_Texture *Explosion = loadTexture("Explosion.png");
	if (x >= Gunner->x - AFFECT_RADIANT && x <= Gunner->x + AFFECT_RADIANT) {
		Gunner->getShot(velocity*5);
	}

	else if (Enemy->x - x < AFFECT_RADIANT && Enemy->x - x > 0) {
		Enemy->x += AFFECT_RADIANT - (Enemy->x - x);
		Enemy->moved = 1;
		Enemy->getShot(velocity*(Enemy->x - x) / (2.0*AFFECT_RADIANT));
		if (Enemy->x > SCREEN_WIDTH) {
			Enemy->HP = 0;
			Enemy->x = SCREEN_WIDTH - Enemy->width;
		}
	}
	else if (x - Enemy->x < AFFECT_RADIANT && x - Enemy->x > 0) {
		Enemy->x -= AFFECT_RADIANT - (x - Enemy->x);
		Enemy->moved = 1;
		Enemy->getShot(velocity*(x - Enemy->x) / (2.0*AFFECT_RADIANT));
		if (Enemy->x < 0) {
			Enemy->HP = 0;
			Enemy->x = 0;
		}
	}
	SDL_RenderClear(gRenderer);
	loadImage(gTexture, 0, 0);
	loadImage(Explosion, x - 10 , y - 10);
	loadPlayer(Gunner, Enemy);
	SDL_Delay(200);
	loadImage(gTexture, 0, 0);
	loadPlayer(Gunner, Enemy);

	x = potentialX;
	y = potentialY;
	velocity = 0;
	check_force = 0;
}

	Bullet::~Bullet()
{
}
