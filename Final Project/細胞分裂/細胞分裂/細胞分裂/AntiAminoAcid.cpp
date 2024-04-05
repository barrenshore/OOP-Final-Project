#include "AntiAminoAcid.h"
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include <time.h>

AntiAminoAcid::AntiAminoAcid(double px, double py, double r)
{
	radius = r;
	PX = px;
	PY = py;
	DifX = PX - BeginX;
	DifY = PY - BeginY;
}

void AntiAminoAcid::draw(SDL_Renderer* r)
{
	//srand(time(NULL));
	aaFilledEllipseRGBA(r, WIDTH / 2 - DifX, HEIGHT / 2 - DifY, radius, radius, 40, 0, 255, 230);
}

void AntiAminoAcid::setP(double x, double y)
{
	PX = x;
	PY = y;
}

double AntiAminoAcid::getPX()
{ return PX; }
double AntiAminoAcid::getPY()
{ return PY; }
void AntiAminoAcid::setV(double vx, double vy) {
	VX = vx;
	VY = vy;
}

void AntiAminoAcid::setDif(Screen& screen) {
	DifX = screen.getX() - PX;
	DifY = screen.getY() - PY;
}

void AntiAminoAcid::move() {
	PX += VX;
	PY += VY;
}

bool AntiAminoAcid::eaten(Cell* cell) {
	if (sqrt((cell->getPX() - PX) * (cell->getPX() - PX) + (cell->getPY() - PY) * (cell->getPY() - PY)) < cell->getR()) {
		if (cell->getR() <= AminoAcidSize && cell == PlayerSplit::player) {
			Cell::STATE = FINISH;
			return 1;
		}
		cell -= *this;
		//cell->setR(sqrt(cell->getR() * cell->getR() - radius * radius));
		return 1;
	}
	return 0;
}

void operator-=(Cell* cell, AntiAminoAcid& anti)
{
	cell->setR(sqrt(cell->getR() * cell->getR() + AminoAcidSize * AminoAcidSize));
}