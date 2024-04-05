#include "Player.h"
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include <stdlib.h>
#include <math.h>


void Player::runMC(bool up, bool down, bool left, bool right) {
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

void Player::draw(SDL_Renderer* r)
{
	aaFilledEllipseRGBA(r, WIDTH / 2 - mDifX, HEIGHT / 2 - mDifY , radius, radius, 255, 90, 40, 230);
}

bool Player::eaten(Cell* cell) {
	mDisX = cell->getPX() - mPosX;
	mDisY = cell->getPY() - mPosY;
	mDis = sqrt(mDisX * mDisX + mDisY * mDisY);
	if (mDis < radius && cell->getR() > radius) return 1;
	return 0;
}
