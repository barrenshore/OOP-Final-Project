#include "System.h"
#include <stdio.h>
#include <SDL.h> // Using SDL
#include "SDL_image.h"  // Using SDL2 image extension library 
#include <SDL_mixer.h>

int System::init()
{
	/*********************************************************/
	// Initialize SDL	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		// Error Handling		
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}
	/*********************************************************/

	// Initialize PNG/JPG loading	
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;  // load support for the JPG and PNG image formats
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}

	return 1;
}

void System::close()
{
	// Quit Mixer subsystem
	Mix_Quit();

	// Quit Image subsystem	
	IMG_Quit();

	// Quit SDL subsystems
	SDL_Quit();
}