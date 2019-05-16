#include "pch.h"
#include "Window.h"
#include "iostream"



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

void loadPlayer(Character* Player1, Character* Player2)
{
	Player2->loadObject();
	Player1->loadObject();
	
	//Update screen
	SDL_RenderPresent(gRenderer);
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadImage(SDL_Texture* texture, int x, int y)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	int run;

	SDL_QueryTexture(texture, NULL, NULL, &(pos.w), &(pos.h));
	
	//Render texture to screen
	if (x == 0 && y == 0)
		run = SDL_RenderCopy(gRenderer, texture, NULL, NULL);
	else 
		run = SDL_RenderCopy(gRenderer, texture, NULL, &pos);
	if (run != 0) std::cout << "Can't coppy" << SDL_GetError() << endl;

	return 1;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	
	SDL_Texture* texture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		Uint32 color_key = SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF);
		SDL_SetColorKey(loadedSurface, SDL_TRUE, color_key);

		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", SDL_GetError());
		}
	}

	return texture;
}

