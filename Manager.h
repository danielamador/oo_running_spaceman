#include <SDL.h>

class Manager
{
	short framesPerSecond;
	short screenWidth;
	short screenHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event eventManager;
	void createWindow(char windowName[], int initX, int initY, int width, int height, Uint32 flags);
	void createRenderer(int driver, Uint32 flags);
	void processMainEvents();

public:
	Manager();
	~Manager();
	void startMain();
};