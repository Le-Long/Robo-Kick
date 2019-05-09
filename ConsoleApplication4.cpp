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

void position(SDL_Rect rect, int x, int y, int w, int h) 
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load background
		gTexture = loadTexture("abc.png");
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
			
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_Rect power_point = { 250, 430, 0, 40 },
				health_bar1 = { 250, 430, 0, 40 },
				health_bar2 = { 250, 430, 0, 40 },
				rect1 = { 0,0,4,4 }, rect2 = { 0,0,4,4 };

			//loadImage("Untitled-1.png", 0, 0);
			Character Player1 = Character("Untitled-2.png");
			Player1.side = 1;
			Character Player2 = Character("Untitled-3.png");
			Player2.side = 0;
			Player1.setPos(570, 390);
			Player2.setPos(130, 390);
			Player1.loadObject();
			Player2.loadObject();

			Bullet Bomb2 = Bullet(Player2, "Untitled-4.png");
			Bomb2.Enemy = Player1;
			Bullet Bomb1 = Bullet(Player1, "Untitled-4.png");
			Bomb1.Enemy = Player2;
			float denta_point_x = Player2.x, 
				denta_point_y = Player2.y ;

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
					if (e.key.keysym.sym == 'p') step = 'p';

					if (step == 'q') 
						SDL_RenderPresent(gRenderer);

					if (step == 'p')
					{
						if (!Bomb2.died)
						{
							Player2.keyEvent(e);
							if (Player2.side == 0 && Player2.x_val != 0) {
								Bomb2.sign = 1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
							}
							else if (Player2.side == 1 && Player2.x_val != 0) {
								Bomb2.sign = -1;
								Bomb2.point_x = Player2.x + 15 + 15.0 * Bomb2.sign;
								Bomb2.point_y = Player2.y + Player2.height;
							}
							
							Bomb2.setPos(Player2.x, Player2.y);
							Bomb2.keyEvent(e);
							if (Bomb2.died) Bomb1.died = 0;

							if (Bomb2.velocity != 0)
								power_point.w = Bomb2.velocity * 8;
							/*if (Bomb2.Gunner.HP != 10)
								health_bar2.w = Bomb2.Gunner.HP * 3;*/
							
							rect2.x = Bomb2.point_x;
							rect2.y = Bomb2.point_y;
							
						}
						else
						{
							Player1.keyEvent(e);
							
							if (Player1.side == 0 && Player1.x_val != 0) {
								Bomb1.sign = 1;
								Bomb1.point_x = Player1.x + 15 + 15.0 * Bomb1.sign;
								Bomb1.point_y = Player1.y + Player1.height;
							}
							else if (Player1.side == 1 && Player1.x_val != 0) {
								Bomb1.sign = -1;
								Bomb1.point_x = Player1.x + 15 + 15.0 * Bomb1.sign;
								Bomb1.point_y = Player1.y + Player1.height;
							}

							Bomb1.setPos(Player1.x, Player1.y);
							Bomb1.keyEvent(e);
							if (Bomb1.died) Bomb2.died = 0;

							if (Bomb1.velocity != 0)
								power_point.w = Bomb1.velocity * 8;
							rect1.x = Bomb1.point_x;
							rect1.y = Bomb1.point_y;
						}
						

						//Update screen
						SDL_RenderPresent(gRenderer);

						loadImage(gTexture, 0, 0);
						Player2.loadObject();
						Player1.loadObject();

						SDL_RenderFillRect(gRenderer, &power_point);
						SDL_RenderFillRect(gRenderer, &rect1);
						SDL_RenderFillRect(gRenderer, &rect2);
						//SDL_RenderFillRect(gRenderer, &health_bar1);
						//SDL_RenderFillRect(gRenderer, &health_bar2);
						cout << denta_point_x << ' ' << denta_point_y << endl;
						
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
