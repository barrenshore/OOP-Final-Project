#include "Screen.h"
#include "constant.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<SDL.h>
#include<SDL2_gfxPrimitives.h>

Screen::Screen(double xx, double yy) 
{
	x = (int)(xx + 0.5), y = (int)(yy + 0.5);
	srand(time(NULL));
	for (int i = 0; i < MAX_MAZE; i++)
	{
		for (int j = 0; j < MAX_MAZE; j++)
		{
			if (i == 0 || j == 0 || i == MAX_MAZE - 1 || j == MAX_MAZE - 1) maze[i][j] = 2; // set wall
			else maze[i][j] = 1; // initial inside
		}
	}
	generatemaze(maze, 1, 1);
	//maze[0][1] = 0, maze[MAX_MAZE - 1][MAX_MAZE - 2] = 0;
	for (int i = 0; i < MAX_MAZE; i++) {
		for (int j = 0; j < MAX_MAZE; j++) {
			printf("%d ", maze[j][i]);
		}
		printf("\n");
	}
}

void Screen::generatemaze(int maze[][MAX_MAZE], int xx, int yy)
{
	int direction;
	maze[xx][yy] = 0; // settle this

	while ((yy + 2 < 21 && maze[xx][yy + 2] == 1) || (xx + 2 < 21 && maze[xx + 2][yy] == 1) || (yy - 2 > 0 && maze[xx][yy - 2] == 1) || (xx - 2 > 0 && maze[xx - 2][yy] == 1))
	{ // if not wall
		direction = rand() % 4 + 1; // decide next
		if (direction == 1 && (yy + 2 < 21 && maze[xx][yy + 2] == 1))
		{ // right
			maze[xx][yy + 1] = 0; // break right
			generatemaze(maze, xx, yy + 2);
		}
		else if (direction == 2 && (xx - 2 > 0 && maze[xx - 2][yy] == 1))
		{ // up
			maze[xx - 1][yy] = 0; // break up
			generatemaze(maze, xx - 2, yy);
		}
		else if (direction == 3 && (yy - 2 > 0 && maze[xx][yy - 2] == 1))
		{ // left
			maze[xx][yy - 1] = 0; // break left
			generatemaze(maze, xx, yy - 2);
		}
		else if (direction == 4 && (xx + 2 < 21 && maze[xx + 2][yy] == 1))
		{ // down
			maze[xx + 1][yy] = 0; // break down
			generatemaze(maze, xx + 2, yy);
		}
	}
}

void Screen::setP(double px, double py)
{ x = (int)(px + 0.5), y = (int)(py + 0.5); }
int Screen::getX() const
{ return x; }
void Screen::setX(int xx)
{ x = xx; }
int Screen::getY() const
{ return y; }
void Screen::setY(int yy)
{ y = yy; }

int Screen::getMaze(int x, int y) const
{	return maze[x / width][y / height]; 
}

void Screen::draw(SDL_Renderer* renderer) {
	left = WIDTH / 2 - (x - width) % width;
	right = left + width;
	up = HEIGHT / 2 - (y - height) % height;
	down = up + height;
	
	if (maze[(x - width) / width][(y - height) / height])
		boxColor(renderer, 0, 0, left, up, 0xAA1111FF);
	else
		boxColor(renderer, 0, 0, left, up, 0xFFAAAAFF);

	if (maze[x / width][(y - height) / height])
		boxColor(renderer, left, 0, right, up, 0xAA1111FF);
	else
		boxColor(renderer, left, 0, right, up, 0xFFAAAAFF);

	if (maze[(x + width) / width][(y - height) / height])
		boxColor(renderer, right, 0, WIDTH, up, 0xAA1111FF);
	else
		boxColor(renderer, right, 0, WIDTH, up, 0xFFAAAAFF);

	if (maze[(x - width) / width][y / height])
		boxColor(renderer, 0, up, left, down, 0xAA1111FF);
	else
		boxColor(renderer, 0, up, left, down, 0xFFAAAAFF);

	if (maze[x / width][y / height])
		boxColor(renderer, left, up, right, down, 0xAA1111FF);
	else
		boxColor(renderer, left, up, right, down, 0xFFAAAAFF);

	if (maze[(x + width) / width][y / height])
		boxColor(renderer, right, up, WIDTH, down, 0xAA1111FF);
	else
		boxColor(renderer, right, up, WIDTH, down, 0xFFAAAAFF);

	if (maze[(x - width) / width][(y + height) / height])
		boxColor(renderer, 0, down, left, HEIGHT, 0xAA1111FF);
	else
		boxColor(renderer, 0, down, left, HEIGHT, 0xFFAAAAFF);

	if (maze[x / width][(y + height) / height])
		boxColor(renderer, left, down, right, HEIGHT, 0xAA1111FF);
	else
		boxColor(renderer, left, down, right, HEIGHT, 0xFFAAAAFF);

	if (maze[(x + width) / width][(y + height) / height])
		boxColor(renderer, right, down, WIDTH, HEIGHT, 0xAA1111FF);
	else
		boxColor(renderer, right, down, WIDTH, HEIGHT, 0xFFAAAAFF);
}

void Screen::setEnd() {
	maze[MAX_MAZE - 1][MAX_MAZE - 2] = 0;
}