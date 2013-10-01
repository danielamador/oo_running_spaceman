#include <SDL.h>
#include "DrawableElement.h"

class Background : public DrawableElement
{
public:
	Background(SDL_Renderer *rendererArg);
	~Background();
	void loadImage(char path[]);
	virtual void putInRenderer();
	virtual void processEvents(const SDL_Event &sdlEvent);
	virtual void updateState();
};