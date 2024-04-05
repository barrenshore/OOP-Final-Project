#pragma once
#include "Enemy.h"
#include "Canon.h"

class Boss:public Enemy
{
	public:
		Boss(int x, int y, int vx, int vy, int r, Screen& screen, Cell* cell) :Enemy(x, y, vx, vy, r, screen, cell) { 
			printf("Boss is constructed, (%.0lf, %.0lf)\n", mPosX, mPosY);
			canon[0] = new Canon(mPosX + radius + CanonSize, mPosY, screen, 0, 1);
			canon[0]->setDif(screen);
			canon[0]->setLimit(NULL, NULL);
			canon[1] = new Canon(mPosX - radius - CanonSize, mPosY, screen, 0, 1);
			canon[1]->setDif(screen);
			canon[1]->setLimit(NULL, NULL);
		}
		~Boss() { printf("\tBoss is destroyed\n"); delete canon[0]; delete canon[1]; }
		void setDis(Cell* cell);
		void setDif(Screen&);
		void Attack(Cell*, Screen& screen, vector<Player*> cells);
		void draw(SDL_Renderer* r);
		bool eaten(Cell* cell, Screen& screen);
	private:
		Canon *canon[2];
		int time1 = 0, time2 = 0;
};

