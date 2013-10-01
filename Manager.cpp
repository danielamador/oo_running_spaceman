#include<SDL.h>
#include "SDL_main.h"
#include<iostream>
#include "Manager.h"
#include "Backgound.h"
#include "Player.h"


Manager::Manager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Manager::~Manager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Manager::createWindow(char windowName[], int initX, int initY, int width, int height, Uint32 flags)
{
	screenHeight = height;
	screenWidth = width;
	window = SDL_CreateWindow(windowName, initX, initY, width, height, flags);
}

void Manager::createRenderer(int driver, Uint32 flags)
{
	renderer = SDL_CreateRenderer(window, driver, flags);
}

void Manager::startMain()
{
	framesPerSecond = 60;
	createWindow("Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	createRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	Background *backElement = new Background(renderer);
	Player *player = new Player();
	backElement->loadImage("1.bmp");
	//backElement->putInRenderer();
	player->loadImage("anything");
	player->putInRenderer();
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}