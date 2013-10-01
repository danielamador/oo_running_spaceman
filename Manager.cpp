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
	Player *player = new Player(renderer);

	backElement->loadImage();
	player->loadImage();
	bool quit = false;

	while(!quit)
	{
		SDL_RenderClear(renderer);
		
		//Used to regulate the frame rate
		Uint32 frameStartTime = SDL_GetTicks();

		//Process any events from the event queue - such as key presses or mouse movements
		while(SDL_PollEvent(&eventManager)) 
		{
			player->processEvents(eventManager);
			if(eventManager.type == SDL_QUIT) 
				quit = true;

			if (eventManager.type == SDL_KEYDOWN) 
			{   //A key has just pressed
				if(eventManager.key.keysym.sym == SDLK_ESCAPE) 
					quit = true;
			}
		}

		player->updateState();
		backElement->putInRenderer();	
		player->putInRenderer();
		SDL_RenderPresent(renderer);


		//Regulate the frame rate
		Uint32 frameTime = SDL_GetTicks() - frameStartTime;
		
		if( frameTime < 1000 / framesPerSecond )
		{
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / framesPerSecond ) - frameTime );
		}
	}
}