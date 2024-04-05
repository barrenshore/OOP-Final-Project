#pragma once
#include<SDL.h>
#include"Image.h"

class AnimeRole
{
public:
	AnimeRole(const char* path, int n, SDL_Renderer* renderer);
	AnimeRole(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	void draw(SDL_Renderer* renderer);
	void startTimer(Uint32 t);
	void stopTimer();
	void setFlag(bool f);

private:
	bool flag;
	char path[100];
	int num;  // New in this example
	Image* image;
	int frame;
	int x;
	int y;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param); // Timer callback 

};

