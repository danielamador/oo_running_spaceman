#include "Backgound.h"
#include "SDL.h"
#include "SDL_main.h"

Background::Background(SDL_Renderer *rendererArg):DrawableElement(rendererArg)//explicitly calling superclass constructor
{
	posX = 0;
	posY = 0;
	width = 640;
	height = 480;
}

void Background::loadImage(char path[])
{
	surface = new SDL_Surface *[1];
	//surface[0] = SDL_LoadBMP(path);
	surface[0] = SDL_LoadBMP("spacemanLarge/spaceman_0001.png");
	if(surface[0] == nullptr)
		std::cout<<"SDL_LoadBMPError!: "<<SDL_GetError()<<std::endl;
	texture = new SDL_Texture *[1];
	texture[0] = SDL_CreateTextureFromSurface(associate_rendr,surface[0]);
	if(texture[0] == nullptr)
		std::cout<<"SDL_CreateTextureFromSurface!: "<<SDL_GetError()<<std::endl;		
}

void Background::putInRenderer()
{
	SDL_RenderCopy(associate_rendr, texture[0], NULL, NULL);
}

void Background::processEvents(const SDL_Event &sdlEvent)
{
	;
}

void Background::updateState()
{
	;
}