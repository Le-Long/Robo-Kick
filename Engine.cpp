#include "pch.h"
#include "Engine.h"

void playerControl(Character* Player, Bullet* Bomb) 
{
	if (Player->side == 0 && Player->x_val != 0) {
		Bomb->sign = 1;
		Bomb->point_x = Player->x + 15 + 15.0 * Bomb->sign;
		Bomb->point_y = Player->y + Player->height;
		Bomb->denta = 0;
	}
	else if (Player->side == 1 && Player->x_val != 0) {
		Bomb->sign = -1;
		Bomb->point_x = Player->x + 15 + 15.0 * Bomb->sign;
		Bomb->point_y = Player->y + Player->height;
		Bomb->denta = 0;
	}

	Bomb->setPos(Player->x, Player->y);
}

bool testHP(Character A, Character B, bool mode)
{
	if (A.HP <= 0) {
		gTexture = loadTexture("player1win.png");
		loadImage(gTexture, 0, 0);
		//Update screen
		SDL_RenderPresent(gRenderer);
		return 0;
	}
	if (B.HP <= 0) {
		if (!mode) gTexture = loadTexture("player2win.png");
		else gTexture = loadTexture("losePVE.png");
		loadImage(gTexture, 0, 0);
		//Update screen
		SDL_RenderPresent(gRenderer);
		return 0;
	}
	return 1;
}
