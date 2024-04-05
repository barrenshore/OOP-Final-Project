#pragma once
#include <SDL.h> // Using SDL

class RenderWindow
{
public:
	RenderWindow(const char* caption, int winx, int winy, int width, int height);
	void close();
	void clear();
	void clear(Uint32 color);
	void display();
	SDL_Renderer* getRenderer();

private:
	SDL_Window* window; // The window we'll be rendering to
	SDL_Renderer* renderer; // The renderer contained by the window
};