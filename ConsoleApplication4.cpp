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

			//loadImage("Untitled-1.png", 0, 0);
			Character Player1 = Character("Untitled-2.png");
			Player1.side = 1;
			Character Player2 = Character("Untitled-3.png");
			Player2.side = 0;
			Character Boss = Character("Boss.png");
			Player1.setPos(570, 390);
			Player2.setPos(70, 390);
			Boss.setPos(470, 250); 
			Boss.width = 225; Boss.height = 150;
						
			Bullet Bomb2 = Bullet(Player2, "Untitled-4.png");
			Bomb2.Enemy = Player1;
			Bullet Bomb1 = Bullet(Player1, "Untitled-4.png");
			Bomb1.Enemy = Player2;
			SDL_Texture* Fire = loadTexture("fire.png");
			const float Fire_length = 110;

			if (Player2.side == 0)
				Bomb2.sign = 1;
			else
				Bomb2.sign = -1;
			Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
			Bomb2.point_y = Player2.y + Player2.height;
			if (Player1.side == 0)
				Bomb1.sign = 1;
			else
				Bomb1.sign = -1;
			Bomb1.point_x = Player1.x + 15 + 15.0 * Bomb1.sign;
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
					//SDL_RenderPresent(gRenderer);
					if (e.key.keysym.sym == 'p')
						step = 'p';
					else if (e.key.keysym.sym == 'e')
						step = 'e';
					if (e.key.keysym.sym == 'q')
						goto MENU;
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
							if (Player2.side == 0 && Player2.x_val != 0) {
								Bomb2.sign = 1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
								Bomb2.denta = 0;
							}
							else if (Player2.side == 1 && Player2.x_val != 0) {
								Bomb2.sign = -1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
								Bomb2.denta = 0;
							}
							
							Bomb2.Gunner = Player2;
							Bomb2.Enemy = Player1;
							Bomb2.setPos(Player2.x, Player2.y);
							Bomb2.keyEvent(e);
							if (Bomb2.died) Bomb1.died = 0;

							if (Bomb2.velocity != 0)
								power_point.w = Bomb2.velocity * 8;
							
							rect2.x = Bomb2.point_x;
							rect2.y = Bomb2.point_y;
							
							Player1 = Bomb2.Enemy;
							Player2 = Bomb2.Gunner; 
							if (Player1.HP >= 0) 
								health_bar1.w = Player1.HP ;
							else health_bar1.w = 0;
							if (Player2.HP >= 0)
								health_bar2.w = Player2.HP;
							else health_bar2.w = 0;
						}
						else
						{
							Player1.keyEvent(e);
							
							if (Player1.side == 0 && Player1.x_val != 0) {
								Player1.x_val = 0;
								Bomb1.sign = 1;
								Bomb1.point_x = Player1.x + 15 + 15.0 * Bomb1.sign;
								Bomb1.point_y = Player1.y + Player1.height;
								Bomb1.denta = 0;
							}
							else if (Player1.side == 1 && Player1.x_val != 0) {
								Player1.x_val = 0;
								Bomb1.sign = -1;
								Bomb1.point_x = Player1.x + 15 + 15.0 * Bomb1.sign;
								Bomb1.point_y = Player1.y + Player1.height;
								Bomb1.denta = 0;
							}

							Bomb1.Gunner = Player1;
							Bomb1.Enemy = Player2;
							Bomb1.setPos(Player1.x, Player1.y);
							Bomb1.keyEvent(e);
							if (Bomb1.died) Bomb2.died = 0;

							if (Bomb1.velocity != 0)
								power_point.w = Bomb1.velocity * 8;
							rect1.x = Bomb1.point_x;
							rect1.y = Bomb1.point_y;

							Player2 = Bomb1.Enemy;
							Player1 = Bomb1.Gunner;
							if (Player1.HP >= 0)
								health_bar1.w = Player1.HP;
							else health_bar1.w = 0;
							if (Player2.HP >= 0)
								health_bar2.w = Player2.HP;
							else health_bar2.w = 0;
						}
						
						loadImage(gTexture, 0, 0);
						Player2.loadObject();
						Player1.loadObject();

						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);
						
						//Update screen
						SDL_RenderPresent(gRenderer);
				
						if (Player1.HP <= 0) {
							gTexture = loadTexture("player1win.png");
							loadImage(gTexture, 0, 0);
							//Update screen
							SDL_RenderPresent(gRenderer);
							goto MENU;
						}
						else if (Player2.HP <= 0) {
							gTexture = loadTexture("player2win.png");
							loadImage(gTexture, 0, 0);
							//Update screen
							SDL_RenderPresent(gRenderer);
							goto MENU;
						}

					}

					if (step == 'e')
					{
						bool fire = 0;
						if (!Bomb2.died)
						{
							Player2.keyEvent(e);
							if (Player2.side == 0 && Player2.x_val != 0) {
								Bomb2.sign = 1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
								Bomb2.denta = 0;
							}
							else if (Player2.side == 1 && Player2.x_val != 0) {
								Bomb2.sign = -1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
								Bomb2.denta = 0;
							}

							fire = 0;

							Bomb2.Gunner = Player2;
							Bomb2.Enemy = Boss;
							Bomb2.setPos(Player2.x, Player2.y);
							Bomb2.keyEvent(e);
							
							if (Bomb2.velocity != 0)
								power_point.w = Bomb2.velocity * 8;

							rect2.x = Bomb2.point_x;
							rect2.y = Bomb2.point_y;

							Boss = Bomb2.Enemy;
							Player2 = Bomb2.Gunner;
							if (Boss.HP >= 0)
								health_bar1.w = Boss.HP;
							else health_bar1.w = 0;
							if (Player2.HP >= 0)
								health_bar2.w = Player2.HP;
							else health_bar2.w = 0;
						}
						if (Bomb2.died)
						{
							Boss.x_val = -Boss.width / 10;
							cout << Boss.x_val;
							for (int i = 0; i++; i < 5)
							{
								Boss.move();
								cout << Boss.x_val;
							}
							if (Boss.x <= Player2.x)
								Player2.HP = 0;
							fire = true;
							if (Boss.x - Fire_length <= Player2.x)
								Player2.HP -= (Fire_length - (Boss.x - Player2.x - Player2.width)/2);
							Bomb2.died = 0;

							if (Boss.HP >= 0)
								health_bar1.w = Boss.HP;
							else health_bar1.w = 0;
							if (Player2.HP >= 0)
								health_bar2.w = Player2.HP;
							else health_bar2.w = 0;
						}

						loadImage(gTexture, 0, 0);
						Boss.loadObject();
						if (fire) loadImage(Fire, Boss.x - Fire_length, Player2.y - 20);
						Player2.loadObject();

						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);

						//Update screen
						SDL_RenderPresent(gRenderer);
						if (fire) SDL_Delay(300);

						loadImage(gTexture, 0, 0);
						Boss.loadObject();
						Player2.loadObject();

						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						SDL_RenderFillRect(gRenderer, &health_bar1);
						SDL_RenderFillRect(gRenderer, &health_bar2);

						//Update screen
						SDL_RenderPresent(gRenderer);

						if (Player1.HP <= 0) {
							gTexture = loadTexture("player1win.png");
							loadImage(gTexture, 0, 0);
							//Update screen
							SDL_RenderPresent(gRenderer);
							goto MENU;
						}
						else if (Boss.HP <= 0) {
							gTexture = loadTexture("player2win.png");
							loadImage(gTexture, 0, 0);
							//Update screen
							SDL_RenderPresent(gRenderer);
							goto MENU;
						}
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
