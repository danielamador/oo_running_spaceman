#include <SDL.h>
//#include "DrawableElement.h"

class Player : public DrawableElement
{
	int velX;
    int velY;
    int speed;
    int currentFrame;
    int totalFrames;
    int direction;
public:
	Player(SDL_Renderer *rendererArg = nullptr);
	~Player();
	void loadImage(char path[]);
	virtual void putInRenderer();
	virtual void processEvents(const SDL_Event &sdlEvent);
	virtual void updateState();
};