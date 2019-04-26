#pragma once
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Image test and apply to surface
bool loadImage(string path, int x, int y);

//Frees image and shuts down SDL
void close();

//Loads individual image
SDL_Texture* loadTexture(std::string path);

#endif

