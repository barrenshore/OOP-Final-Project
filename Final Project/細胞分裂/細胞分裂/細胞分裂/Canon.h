#pragma once
#include <stdlib.h>
#include <vector>
#include "Player.h"
#include "AntiAminoAcid.h"

class Canon
{
public:
	Canon(double x, double y, Screen &screen, double, double);
	~Canon() { printf("\tCanon is destroyed\n"); };
	void setP(double, double);
	double getPX() const;
	double getPY() const;
	void setDif(Screen& screen);
	double getDis() const;
	void setDis(Cell* cell);
	void setLimit(int, int);
	void AimAndShoot(Cell* cell);
	void recollect(Screen& screen, std::vector<Player*>);

	bool eaten(Cell*);
	void draw(SDL_Renderer* r);
private:
	AntiAminoAcid anti[BulletCount];
	bool shoted[BulletCount] = {0};
	double PX;
	double PY;
	double DisX;
	double DisY;
	double Dis;
	int limit_start = 0;
	int limit_end = 180;
	int time = 0;
	int bulletNum = 0;
	int OriginX;
	int OriginY;
	double DifX;
	double DifY;
	int theta = 0;
	int start = 85;
	int end = 95;
};

