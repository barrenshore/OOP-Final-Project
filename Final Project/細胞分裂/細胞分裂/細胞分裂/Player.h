#pragma once
#include "Cell.h"

class Player: public Cell
{
public:
	Player(int x, int y, int vx, int vy, int r, Screen& screen, Cell* cell):Cell(x, y, vx, vy, r, screen, cell) { printf("Player is constructed\n"); }
	~Player() { printf("\tPlayer is destroyed\n"); }
	void runMC(bool, bool, bool, bool);
	void draw(SDL_Renderer* r); // Draw
	bool eaten(Cell* cell);
private:
};

