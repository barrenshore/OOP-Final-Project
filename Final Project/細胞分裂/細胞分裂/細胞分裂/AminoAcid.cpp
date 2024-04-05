#include "AminoAcid.h"
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include "constant.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void AminoAcid::draw(SDL_Renderer* r)
{
	//srand(time(NULL));
	aaFilledEllipseRGBA(r, WIDTH / 2 - DifX, HEIGHT / 2 - DifY, radius, radius, 255, 0, 40, 230);
}

void AminoAcid::setP(double x, double y)
{
	PX = x;
	PY = y;
}

void AminoAcid::setDif(Screen& screen) {
	DifX = screen.getX() - PX;
	DifY = screen.getY() - PY;
	Dif = sqrt(DifX * DifX + DifY * DifY);
}

double AminoAcid::getDif()
{ return Dif; }

bool AminoAcid::eaten(Cell* cell) {
	if (sqrt((cell->getPX() - PX) * (cell->getPX() - PX) + (cell->getPY() - PY) * (cell->getPY() - PY)) < cell->getR()) {
		//cell->setR(sqrt(radius * radius + cell->getR() * cell->getR()));
		cell += *this;
		return 1;
	}
	return 0;
}

void AminoAcid::generateAmino(Screen& screen, Cell *cell) {
	double dX = 0, dY = 0;
	do
	{
		dX = 2 * (rand() % width) - width;
		dY = 2 * (rand() % height) - height;
	} while (screen.getMaze(cell->getPX() + dX, cell->getPY() + dY));
	PX = cell->getPX() + dX;
	PY = cell->getPY() + dY;
}

double AminoAcid::getR()
{
	return radius;
}

void operator+=(Cell* cell, AminoAcid& amino)
{
	cell->setR(sqrt(cell->getR() * cell->getR() + amino.getR() * amino.getR()));
}
