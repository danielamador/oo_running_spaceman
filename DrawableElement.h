#include<SDL.h>
#include<iostream>

class DrawableElement
{
	protected:
		int posX;
		int posY;
		int width;
		int height;
		SDL_Renderer *associate_rendr;
		SDL_Surface **surface;
		SDL_Texture **texture;
	public:
		DrawableElement(SDL_Renderer *rendererArg = nullptr);
		~DrawableElement();
		virtual void loadImage(char path[]) = 0;
		virtual void putInRenderer() = 0;
		virtual void processEvents(const SDL_Event &sdlEvent) = 0;
		virtual void updateState() = 0;
};