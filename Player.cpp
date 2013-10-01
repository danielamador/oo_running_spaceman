#include "DrawableElement.h"
#include "Player.h"
#include "SDL.h"
#include "SDL_image.h"
#include <cstdio>

Player::Player(SDL_Renderer *renderer_arg):DrawableElement(renderer_arg)	
{
    posX = 20;
	posY = 20;
	velX = 0;
	velY = 0;
	speed = 4;
	currentFrame = 0;
	totalFrames = 48;
	direction = 0;
	width = 100;
	height = 100;
	surface = new SDL_Surface *[8];
	texture = new SDL_Texture *[8];
}


Player::~Player()
{
    //Free any loaded images
    for(int i=0; i<8; ++i) 
	{
		SDL_DestroyTexture(texture[i]);
    }
}

void Player::loadImage()
{
	char filename[200];
	for(short register index=0; index<8; ++index) 
	{
        sprintf(filename, "spacemanLarge/spaceman_%04d.png", index);
		//Load the image
        surface[index] = IMG_Load(filename);
		if(surface[index] == nullptr)
			std::cout<<"Load Image: SDL_LoadBMPError!: "<<SDL_GetError()<<std::endl;
		texture[index] = SDL_CreateTextureFromSurface(associate_rendr, surface[index]);
		SDL_FreeSurface(surface[index]);//since I don't need the surfaces anymore, I can free them
		                              //In my tests, it's saving about 15MB in RAM

    }
	
}

void Player::updateState()
{
	short screenWidth = 640;
	short screenHeight = 480;
    //move the character, using the velocity
    posX += velX;
    posY += velY;

    //check if the character has moved out the edge of the screen
    if(posX < 0-25) 
	{
        posX = -25;
		velX = 0;
		currentFrame = 1;
		//posX += screenWidth + width;//makes the character appear in the otther sile
    } 
	else if(posX > screenWidth - width + 25) 
	{
        posX = screenWidth - width + 25;
		velX = 0;
		currentFrame = 1;
		//posX -= (screenWidth + width);
    }

    if(posY < 0) 
	{
		posY = 0;
        velY = 0;
		currentFrame = 1;
		//posY += screenHeight + height;
    }
	else if(posY > screenHeight - height) 
	{
		posY = screenHeight - height;
		velY = 0;
		currentFrame = 1;
       // posY -= (screenHeight + height);
    }

    bool isMoving = true;

    //update the direction based on the velocity
    if(velY > 0) 
	{
        if(velX > 0) 
            direction = 1; 
		else if(velX < 0)
            direction = 7;
		else 
            direction = 0;
    } 
	else if(velY < 0) 
	{
        if(velX > 0)
            direction = 3;
		else if(velX < 0)
            direction = 5;
        else 
            direction = 4;
    } 
	
	else 
	{ //velY == 0 
        if(velX > 0) 
            direction = 2;
        else if(velX < 0)
            direction = 6;
        else 
		{ //velX == 0
            isMoving = false;
            currentFrame = 0;
        }
    }

    if(isMoving) 
	{
        //increment and loop the animation index
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void Player::putInRenderer()
{
    //Set the source rectangle
    SDL_Rect srcRect;
    srcRect.x = (currentFrame % 6) * width; //horizontal, that's why it's module
    srcRect.y = (currentFrame / 6) * height;
    srcRect.w = width;
    srcRect.h = height;

    //Set the desRect based on the position
    SDL_Rect dstRect;
    dstRect.x = posX;
    dstRect.y = posY;
	dstRect.w = width;
	dstRect.h = height;
    //Draw the character to the screen
	SDL_RenderCopy(associate_rendr, texture[direction], &srcRect, &dstRect);
}

void Player::processEvents(const SDL_Event &sdlEvent)
{
    if (sdlEvent.type == SDL_KEYDOWN) {   //A key has just pressed
        switch(sdlEvent.key.keysym.sym)
        {
            case SDLK_LEFT:
                //Left key was just pressed
                velX = -speed;
                break;
            case SDLK_RIGHT:
                //Right key was just pressed
                velX = speed;
                break;
            case SDLK_UP:
                //Left key was just pressed
                velY = -speed;
                break;
            case SDLK_DOWN:
                //Right key was just pressed
                velY = speed;
                break;
        }
    } 
    if (sdlEvent.type == SDL_KEYUP) {    //A key has just been released
        switch(sdlEvent.key.keysym.sym)
        {
            case SDLK_LEFT:
                //Left key was just released
                velX = 0;
                break;
            case SDLK_RIGHT:
                //Right key was just released
                velX = 0;
                break;
            case SDLK_UP:
                //Left key was just released
                velY = 0;
                break;
            case SDLK_DOWN:
                //Right key was just released
                velY = 0;
                break;
        }
    }
}
