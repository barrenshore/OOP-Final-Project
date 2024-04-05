#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"

class PauseScreen
{
	public:
		void draw(SDL_Renderer* r); // Draw
		void setVolume(int, int);
		int getMusic() const;
		int getAudio() const;
	private:
		int music = 32;
		int audio = 32;
};

