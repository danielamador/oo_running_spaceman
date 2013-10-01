#include "SDL.h"
#include "SDL_main.h"
#include "Manager.h"
#include <iostream>

int main(int argc, char *argv[])//I don't know why, but if you don't put argc and argv in the main, the program don't compile
{
	std::cout<<"ajlksdjklasdjalskdjalksdjkal";
	Manager *manager = new Manager();
	manager->startMain();
	return 0;
}