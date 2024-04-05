#include "StaticRole.h"
#include "Image.h"
#include <stdio.h>
#include "constant.h"

StaticRole::StaticRole(const char* path, SDL_Renderer* renderer)
{
	image.set(path, renderer);
}

StaticRole::StaticRole(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	image.set(path, renderer, r, g, b);
}

void StaticRole::close()
{
	image.close();
}

void StaticRole::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int StaticRole::getWidth()
{
	return image.getWidth();
}

int StaticRole::getHeight()
{
	return image.getHeight();
}

void StaticRole::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = image.getWidth();
	d.h = image.getHeight();

	image.draw(renderer, d, { NULL });
}
