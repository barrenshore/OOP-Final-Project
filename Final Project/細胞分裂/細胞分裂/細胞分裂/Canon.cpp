#include "Canon.h"
#include <SDL2_gfxPrimitives.h>

Canon::Canon(double x, double y, Screen& screen, double dx, double dy) {
	PX = x;
	PY = y;
	DisX = dx;
	DisY = dy;
	Dis = sqrt(DisX * DisX + DisY * DisY);
	OriginX = PX + DisX * AminoAcidSize;
	OriginY = PY + DisY * AminoAcidSize;
	for (int i = 0; i < BulletCount; i++) anti[i].setP(OriginX, OriginY);

	DifX = screen.getX() - PX;
	DifY = screen.getY() - PY;
	for (int i = 0; i < BulletCount; i++) {
		anti[i].setDif(screen);
	}

	theta = (180 * atan(DisY / DisX) / M_PI + 0.5);
	if (DisX < 0) theta += 180;
	if (theta < 0) theta = (theta + 360) % 360;
	limit_start = (theta + 270) % 360;
	limit_end = (theta + 90) % 360;
	printf("(%.0lf, %.0lf) (%.0lf, %.0lf) (theta: %d, %d, %d)\n", PX, PY, DisX, DisY, theta, limit_start, limit_end);
}

void Canon::setP(double x, double y) {
	PX = x;
	PY = y;
	for (int i = 0; i < BulletCount; i++) {
		anti[i].setP(x, y);
	}
}
double Canon::getPX() const
{ return PX; }
double Canon::getPY() const
{ return PY; }

void Canon::setDif(Screen& screen) {
	DifX = screen.getX() - PX;
	DifY = screen.getY() - PY;
	for (int i = 0; i < BulletCount; i++) {
		anti[i].setDif(screen);
	}
}

double Canon::getDis() const
{ return Dis; }
void Canon::setDis(Cell* cell) {
	DisX = cell->getPX() - PX;
	DisY = cell->getPY() - PY;
	Dis = sqrt(DisX * DisX + DisY * DisY);
	theta = (180 * atan(DisY / DisX) / M_PI + 0.5);
	if (DisX < 0) theta += 180;
	if (theta < 0) theta = (theta + 360) % 360;
}
void Canon::setLimit(int start, int end) {
	limit_start = start;
	limit_end = end;
}

void Canon::AimAndShoot(Cell* cell) {
	if ((limit_start < limit_end && (theta > limit_start && theta < limit_end)) || (limit_start > limit_end && (theta > limit_start || theta < limit_end))) {
		start = theta - 5;
		end = theta + 5;
		for (int i = 0; i < BulletCount; i++) {
			anti[bulletNum].setV(BulletVelocity * DisX / Dis, BulletVelocity * DisY / Dis);
		}
		if (time > 80) {
			shoted[bulletNum++] = 1;
			if (bulletNum == BulletCount) {
				bulletNum = 0;
			}
			time = 0;
		}
		else {
			time++;
		}
	}
}

void Canon::recollect(Screen& screen, std::vector<Player*> cells) {
	for (int i = 0; i < BulletCount; i++) {
		if (shoted[i]) {
			anti[i].move();
			for (int j = 0; j < cells.size(); j++) {
				if (anti[i].eaten(cells[j])) {
					anti[i].setP(OriginX, OriginY);
					anti[i].setV(0, 0);
					shoted[i] = 0;
					break;
				}
			}
			if (!shoted[i]) continue;
			if (screen.getMaze(anti[i].getPX(), anti[i].getPY())) {
				anti[i].setP(OriginX, OriginY);
				anti[i].setV(0, 0);
				shoted[i] = 0;
			}
		}
	}
}

bool Canon::eaten(Cell* cell) {
	DisX = cell->getPX() - PX;
	DisY = cell->getPY() - PY;
	Dis = sqrt(DisX * DisX + DisY * DisY);
	if (Dis < CanonSize && cell->getR() > CanonSize) {
		cell->setR(sqrt(CanonSize * CanonSize + cell->getR() * cell->getR()));
		return 1;
	}
	return 0;
}

void Canon::draw(SDL_Renderer* r) {
	for (int i = 0; i < BulletCount; i++) {
		anti[i].draw(r);
	}
	aaFilledEllipseRGBA(r, WIDTH / 2 - DifX, HEIGHT / 2 - DifY, CanonSize, CanonSize, 90, 90, 90, 230);
	filledPieRGBA(r, (int)(WIDTH / 2.0 - DifX + 0.5), (int)(HEIGHT / 2.0 - DifY + 0.5), BarrelSize, start, end, 255, 255, 255, 255);
}
