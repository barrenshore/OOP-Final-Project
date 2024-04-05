#pragma once
#include "Player.h"

class PlayerSplit : public Player
{
public:
	PlayerSplit(int x, int y, int vx, int vy, int r, Screen& screen) :Player(x, y, vx, vy, r, screen, player) { printf("PlayerSplit is constructed\n"); time = 0;};
	~PlayerSplit() { printf("\tPlayerSplit is destroyed\n"); }
	void runSplit(bool, bool, bool, bool);
	int getT() const;
	void setT();
	void run(bool, bool, bool, bool);
	void draw(SDL_Renderer* r); // Draw
	bool eaten(Cell* cell);

	static Cell* player;
private:
	// time after split from the mother cell
	int time;
};

