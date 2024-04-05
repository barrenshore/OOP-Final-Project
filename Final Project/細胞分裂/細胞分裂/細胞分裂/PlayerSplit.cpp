#include "PlayerSplit.h"
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include <stdlib.h>

int PlayerSplit::getT() const
{ return time; }
void PlayerSplit::setT()
{ time++; }

void PlayerSplit::runSplit(bool up, bool down, bool left, bool right) {
	if ((up && left) || (up && right) || (down && left) || (down && right))
	{
		if (up && left)
		{
			mVelX -= VELOCITY / radius / radius / sqrt(2);
			mVelY -= VELOCITY / radius / radius / sqrt(2);
		}
		else if (up && right)
		{
			mVelX += VELOCITY / radius / radius / sqrt(2);
			mVelY -= VELOCITY / radius / radius / sqrt(2);
		}
		else if (down && left)
		{
			mVelX -= VELOCITY / radius / radius / sqrt(2);
			mVelY += VELOCITY / radius / radius / sqrt(2);
		}
		else if (down && right)
		{
			mVelX += VELOCITY / radius / radius / sqrt(2);
			mVelY += VELOCITY / radius / radius / sqrt(2);
		}
	}
	else
	{
		if (up) mVelY -= VELOCITY / radius / radius;
		if (left) mVelX -= VELOCITY / radius / radius;
		if (down) mVelY += VELOCITY / radius / radius;
		if (right) mVelX += VELOCITY / radius / radius;
	}
}

void PlayerSplit::draw(SDL_Renderer* r)
{
	/*for (int theta = 0; theta < 360; theta += 30)
	{
		int x = 0;
		int y = -150;
		double th = (double)theta / 180 * M_PI;
		double xv = x * cos(th) + y * sin(th);
		double yv = -x * sin(th) + y * cos(th);
		filledPieRGBA(r, mPosX, mPosY, M_WIDTH + 8, theta, theta + 10, 255, 255, 128, 255);
	}*/

	aaFilledEllipseRGBA(r, WIDTH / 2 - mDifX, HEIGHT / 2 - mDifY, radius, radius, 200, 90, 40, time % 256);
	
	/*for (int i = 0; i < 5; i++)
	{
		aaFilledEllipseRGBA(r, (mPosX - M_WIDTH) + rand() % (M_WIDTH * 2), (mPosY - M_HEIGHT) + rand() % (M_HEIGHT * 2), 3, 3, 255, 255, 128, 200);
	}*/
}

bool PlayerSplit::eaten(Cell* cell) {
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
	if (mDis < radius && (cell->getR() > radius || cell == player)) {
		cell->setR(sqrt(radius * radius + cell->getR() * cell->getR()));
		return 1;
	}
	return 0;
}
