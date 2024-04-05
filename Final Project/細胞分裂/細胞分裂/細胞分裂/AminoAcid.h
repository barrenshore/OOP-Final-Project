#pragma once
#include "Cell.h"
#include <stdlib.h>

class AminoAcid
{
public:
	AminoAcid() { PX = 0, PY = 0, DifX = 0, DifY = 0, Dif = 0, radius = rand() % AminoAcidSize; }
	void setP(double, double);
	void setDif(Screen &screen);
	double getDif();
	void draw(SDL_Renderer* r); // Draw
	bool eaten(Cell*);
	void generateAmino(Screen& screen, Cell *cell);
	double getR();
	friend void operator+=(Cell* cell, AminoAcid& amino);

private:
	double PX;
	double PY;
	double DifX;
	double DifY;
	double Dif;
	double radius;
};

