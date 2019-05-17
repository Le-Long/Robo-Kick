// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SDL.h>
#include <SDL_image.h>
#undef main
#include <iostream>
#include <string>
#include "Window.h"
#include "Character.h"
#include "Bullet.h"
#include <vector>
#include "Engine.h"

using namespace std;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		MENU:
		//Load background
		gTexture = loadTexture("Patrollers_Mammoth.png");
		if (!loadImage(gTexture,0,0))
		{
			printf("Failed to load background!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			
			gTexture = loadTexture("abc.png");
			
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_Rect power_point = { 250, 430, 0, 40 },
				health_bar1 = { 570, 450, 50, 20 },
				health_bar2 = { 70, 450, 50, 20 },
				rect1 = { 0,0,4,4 }, rect2 = { 0,0,4,4 };

			Character Player1 = Character("U-2.png");
			Player1.side = 1;
			Character Player2 = Character("U-3.png");
			Player2.side = 0;
			Character Boss = Character("Boss.png");
			Player1.setPos(570, 385);
			Player2.setPos(70, 385);
			Boss.setPos(470, 295); 
			Boss.width = 189; Boss.height = 129;
			Boss.HP = 300;
						
			Bullet Bomb2 = Bullet(Player2, "Untitled-4.png");
			Bullet Bomb1 = Bullet(Player1, "Untitled-4.png");
			SDL_Texture* Fire = loadTexture("fire.png");
			const float Fire_length = 110;
			float Fire_x;

			if (Player2.side == 0)
				Bomb2.sign = 1;
			else
				Bomb2.sign = -1;
			Bomb2.point_x = Player2.x + 12.5 + 20.0 * Bomb2.sign;
			Bomb2.point_y = Player2.y + Player2.height;
			if (Player1.side == 0)
				Bomb1.sign = 1;
			else
				Bomb1.sign = -1;
			Bomb1.point_x = Player1.x + 12.5 + 20.0 * Bomb1.sign;
			Bomb1.point_y = Player1.y + Player1.height;

			char step = 'q';

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}

					int mouse_x, mouse_y;
					SDL_GetMouseState(&mouse_x, &mouse_y);
					if (mouse_x > 190 && mouse_x < 212 && mouse_y < 228 && mouse_y > 199 
						&& e.type == SDL_MOUSEBUTTONDOWN) step = 'p';
					else if (mouse_x > 100 && mouse_x < 120 && mouse_y < 135 && mouse_y > 125
						&& e.type == SDL_MOUSEBUTTONDOWN) step = 'e';

					if (e.key.keysym.sym == 'p')
						step = 'p';
					else if (e.key.keysym.sym == 'e')
						step = 'e';
					if (step == 'q')
					{
						SDL_RenderPresent(gRenderer);
					}

					if (step == 'p')
					{
						if (e.key.keysym.sym == 'q')
							goto MENU;
						else if (!Bomb2.died)
						{
							Player2.keyEvent(e);

							Bomb2.Gunner = &Player2;
							Bomb2.Enemy = &Player1;
							playerControl(&Player2, &Bomb2);
							Bomb2.keyEvent(e);
							if (Bomb2.died) Bomb1.died = 0;

							if (Bomb2.velocity != 0)
								power_point.w = Bomb2.velocity * 8;
							rect2.x = Bomb2.point_x;
							rect2.y = Bomb2.point_y;
						}
						else
						{
							Player1.keyEvent(e);
							Bomb1.Gunner = &Player1;
							Bomb1.Enemy = &Player2;
							playerControl(&Player1, &Bomb1);
							Bomb1.keyEvent(e);
							if (Bomb1.died) Bomb2.died = 0;

							if (Bomb1.velocity != 0)
								power_point.w = Bomb1.velocity * 8;
							rect1.x = Bomb1.point_x;
							rect1.y = Bomb1.point_y;
						}
						
						if (Player1.HP >= 0)
							health_bar1.w = Player1.HP;
						else health_bar1.w = 0;
						if (Player2.HP >= 0)
							health_bar2.w = Player2.HP;
						else health_bar2.w = 0;

						loadImage(gTexture, 0, 0);
						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);
						loadPlayer(&Player1, &Player2);
										
						if (!testHP(Player1, Player2 ,0)) goto MENU;

					}

					if (step == 'e')
					{
						if (e.key.keysym.sym == 'q')
							goto MENU;
						bool fire = 0;
						if (!Bomb2.died)
						{
							fire = 0;
							Player2.keyEvent(e);
							Bomb2.Gunner = &Player2;
							Bomb2.Enemy = &Boss;
							playerControl(&Player2, &Bomb2);
							Bomb2.keyEvent(e);
							
							if (Bomb2.velocity != 0)
								power_point.w = Bomb2.velocity * 8;

							rect2.x = Bomb2.point_x;
							rect2.y = Bomb2.point_y;

						}
						if (Bomb2.died)
						{
							Boss.x_val = -10;
							Boss.move();
							Boss.move();
							Boss.move();
							Boss.move();
							Boss.move();
							if (Boss.x <= Player2.x)
								Player2.HP = 0;
							fire = true;
							if (Fire_x <= Player2.x + Player2.width && Fire_x + Fire_length >= Player2.x)
								Player2.getShot(20);
							Bomb2.died = 0;
						}

						if (Boss.HP >= 0)
							health_bar1.w = Boss.HP;
						else health_bar1.w = 0;
						if (Player2.HP >= 0)
							health_bar2.w = Player2.HP;
						else health_bar2.w = 0;

						loadImage(gTexture, 0, 0);
						Fire_x = Boss.x - Fire_length - 2*(300 - Boss.HP);
						if (Fire_x <= 0) Fire_x = 0;
						if (fire) loadImage(Fire, Fire_x, Player2.y - 20);
						if (!testHP(Boss, Player2, 1)) goto MENU;

						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);

						//Update screen
						loadPlayer(&Boss, &Player2);

						if (fire) SDL_Delay(300);
						loadImage(gTexture, 0, 0);
						
						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);

						//Update screen
						loadPlayer(&Boss, &Player2);

						
					}
				}
			}
		}
	}//
	//Free resources and close SDL
	close();
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
