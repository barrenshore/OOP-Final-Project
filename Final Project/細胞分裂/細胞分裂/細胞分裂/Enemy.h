#pragma once
#include "Cell.h"
#include <SDL.h>
#include <stdio.h>
#include <vector>
using namespace std;

class Enemy: public Cell
{
public:
	Enemy(int x, int y, int vx, int vy, int r, Screen& screen, Cell* cell) :Cell(x, y, vx, vy, r, screen, cell) { printf("Enemy is constructed\n"); }
	~Enemy() { printf("\tEnemy is destroyed\n"); }
	void ChaseAndRun(Cell*, Cell*, Cell*);
	void draw(SDL_Renderer* r); // Draw
	bool eaten(Cell* cell);
private:
	double min_sin = 0, min_cos = 1;
	double small_sin = 0, small_cos = 1;
	double ally_sin = 0, ally_cos = 1;
};

