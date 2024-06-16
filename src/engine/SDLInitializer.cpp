// Local includes
#include "SDLInitializer.h"

// SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// std includes
#include <iostream>

SDLInitializer::SDLInitializer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL init error" << std::endl;
		exit(1);
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
		std::cerr << "Error SDL2_image Initialization";
		exit(1);
	}

	if (TTF_Init() < 0) {
		std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		exit(1);
	}
}

SDLInitializer::~SDLInitializer()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
