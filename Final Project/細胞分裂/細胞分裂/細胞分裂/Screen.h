#pragma once
#include <SDL.h>
#include "constant.h"

class Screen
{
	public:
		Screen(double, double);
		void generatemaze(int[][MAX_MAZE], int, int);
		void setP(double, double);
		void setX(int);
		int getX() const;
		void setY(int);
		int getY() const;
		int getMaze(int, int) const;
		void draw(SDL_Renderer* r); // Draw

		void setEnd();
	private:
		// position of the center of the screen 
		int x, y;
		int left, right, up, down;
		int maze[MAX_MAZE][MAX_MAZE];
};

