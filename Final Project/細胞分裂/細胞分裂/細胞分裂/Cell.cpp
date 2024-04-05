#include "Cell.h"
#include <SDL.h> // Using SDL
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include <stdlib.h>

Cell::Cell(double x, double y, double vx, double vy, double r, Screen& screen, Cell* cell)
{
	mPosX = x;
	mPosY = y;
	mVelX = vx;
	mVelY = vy;
	radius = r;
	mDifX = screen.getX() - mPosX;
	mDifY = screen.getY() - mPosY;
	if (cell == NULL) {
		mDisX = 0;
		mDisY = 0;
	}
	else {
		mDisX = cell->getPX() - mPosX;
		mDisY = cell->getPY() - mPosY;
	}
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
}

double Cell::getPX() const
{ return mPosX; }
double Cell::getPY() const
{ return mPosY; }
void Cell::setPX(double x)
{ mPosX = x; }
void Cell::setPY(double y)
{ mPosY = y; }

double Cell::getVX() const
{ return mVelX; }
double Cell::getVY() const
{ return mVelY; }
double Cell::getV() const
{ return (sqrt(mVelX * mVelX + mVelY * mVelY)); }
void Cell::setVX(double x)
{ mVelX = x; }
void Cell::setVY(double y)
{ mVelY = y; }

double Cell::getR() const
{ return radius; }
void Cell::setR(double r)
{ radius = r; }

void Cell::move()
{
	mPosX+=mVelX;
	mPosY+=mVelY;
}

void Cell::setDif(Screen& screen) {
	mDifX = screen.getX() - mPosX;
	mDifY = screen.getY() - mPosY;
}

void Cell::setDis(Cell* cell)
{
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
}
double Cell::getDisX() const
{ return mDisX; }
double Cell::getDisY() const
{ return mDisY; }
double Cell::getDis() const
{ return mDis; }

void Cell::resistance()
{
	if (mVelX > 0) {
		mVelX = mVelX - 5 * mVelX * mVelX / radius / radius;
	}
	else if (mVelX < 0) {
		mVelX = mVelX + 5 * mVelX * mVelX / radius / radius;
	}
	if (mVelY > 0) {
		mVelY = mVelY - 5 * mVelY * mVelY / radius / radius;
	}
	else if (mVelY < 0) {
		mVelY = mVelY + 5 * mVelY * mVelY / radius / radius;
	}
}
void Cell::hitWall(Screen& screen) {
	if (screen.getMaze(mPosX - radius, mPosY) || screen.getMaze(mPosX + radius, mPosY))
	{	//Move back
		hitwall = true;
		mPosX -= mVelX;
		mVelX *= -1;
	}
	else if (screen.getMaze(mPosX, mPosY - radius) || screen.getMaze(mPosX, mPosY + radius))
	{	//Move back
		hitwall = true;
		mPosY -= mVelY;
		mVelY *= -1;
	}
	else
		hitwall = false;
}

bool Cell::eaten(Cell* cell) {
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
	if (mDis < radius && cell->getR() > radius) {
		cell->setR(sqrt(radius * radius + cell->getR() * cell->getR()));
		return 1;
	}
	return 0;
}

bool Cell::ishitwall() const
{
	return hitwall;
}