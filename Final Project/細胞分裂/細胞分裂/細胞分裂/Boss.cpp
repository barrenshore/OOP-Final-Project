#include "Boss.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void Boss::setDis(Cell* cell) {
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
	if (canon[0]) {
		canon[0]->setP(mPosX + (radius + CanonSize) * -1 * mDisY / mDis, mPosY + (radius + CanonSize) * mDisX / mDis);
		canon[0]->setDis(cell);
	}
	if (canon[1]) {
		canon[1]->setP(mPosX + (radius + CanonSize) * mDisY / mDis, mPosY + (radius + CanonSize) * -1 * mDisX / mDis);
		canon[1]->setDis(cell);
	}
}

void Boss::setDif(Screen& screen) {
	Cell::setDif(screen);
	if (canon[0]) canon[0]->setDif(screen);
	if (canon[1]) canon[1]->setDif(screen);
}

void Boss::Attack(Cell* min, Screen& screen, vector<Player*> cells) {
	if (min) {
		if (canon[0]) canon[0]->AimAndShoot(min);
		if (canon[1]) canon[1]->AimAndShoot(min);
	}
	if (canon[0]) canon[0]->recollect(screen, cells);
	if (canon[1]) canon[1]->recollect(screen, cells);
}

void Boss::draw(SDL_Renderer* r) {
	aaFilledEllipseRGBA(r, WIDTH / 2 - mDifX + 0.5, HEIGHT / 2 - mDifY, radius + 0.5, radius, 255, 90, 40, 230);
	canon[0]->draw(r);
	canon[1]->draw(r);
}

bool Boss::eaten(Cell* cell, Screen& screen) {	
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
	if (canon[0] || canon[1]) {
		if (canon[0]) {
			if (canon[0]->eaten(cell)) {
				delete canon[0];
			}
		}
		else {
			if (time1 > 1000) {
				canon[0] = new Canon(mPosX + (radius + CanonSize) * -1 * mDisY / mDis, mPosY + (radius + CanonSize) * mDisX / mDis, screen, 0, 1);
				time1 = 0;
			}
			else {
				time1++;
			}
		}
		if (canon[1]) {
			if (canon[1]->eaten(cell)) {
				delete canon[1];
			}
		}
		else {
			if (time1 > 1000) {
				canon[1] = new Canon(mPosX + (radius + CanonSize) * mDisY / mDis, mPosY + (radius + CanonSize) * -1 * mDisX / mDis, screen, 0, 1);
				time2 = 0;
			}
			else {
				time2++;
			}
		}
	}
	else {
		if (mDis < radius && cell->getR() > radius) {
			cell->setR(sqrt(radius * radius + cell->getR() * cell->getR()));
			return 1;
		}
	}
	
	return 0;
}