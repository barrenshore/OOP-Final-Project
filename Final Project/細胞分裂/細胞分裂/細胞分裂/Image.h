#pragma once
#include<SDL.h>

class Image
{
public:
	Image();
	Image(const char* path, SDL_Renderer* renderer);
	Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void set(const char* path, SDL_Renderer* renderer);
	void set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
	int getWidth();
	int getHeight();

private:
	char path[100];
	SDL_Texture* texture;
	int width;
	int height;
};

