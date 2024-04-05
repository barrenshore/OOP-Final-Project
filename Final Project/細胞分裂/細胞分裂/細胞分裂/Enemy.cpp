#include "Enemy.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <math.h>

void Enemy::draw(SDL_Renderer* r)
{
	aaFilledEllipseRGBA(r, WIDTH / 2 - mDifX, HEIGHT / 2 - mDifY, radius, radius, 0, 90, 255, 230);
}

void Enemy::ChaseAndRun(Cell* min, Cell* small, Cell* ally)
{
	// min && small must be exist at the same time
	if (min && small) {
		setDis(min);
		min_sin = mDisY / mDis, min_cos = mDisX / mDis;
		setDis(small);
		small_sin = mDisY / mDis, small_cos = mDisX / mDis;
		if (min->getR() < radius)
		{
			mVelX = EnemyVelocity * min_cos;
			mVelY = EnemyVelocity * min_sin;
		}
		else { // min must be bigger than enemy
			if (small->getR() < radius && (min_sin / small_sin <= 0 || min_cos / small_cos <= 0)) {
				mVelX = EnemyVelocity * small_cos;
				mVelY = EnemyVelocity * small_sin;
			}
			else {
				if (ally) {
					setDis(ally);
					ally_sin = mDisX / mDis, ally_cos = mDisX / mDis;
					mVelX = EnemyVelocity * ally_cos;
					mVelY = EnemyVelocity * ally_sin;
				}
				else {
					if (min == small) {
						mVelX = EnemyVelocity * -1 * small_cos;
						mVelY = EnemyVelocity * -1 * small_sin;
					}
					else {
						mVelX = EnemyVelocity * -2 * (min_cos + small_cos) / ((min_cos + small_cos) * (min_cos + small_cos) + (min_sin + small_sin) * (min_sin * small_sin));
						mVelY = EnemyVelocity * -2 * (min_sin + small_sin) / ((min_cos + small_cos) * (min_cos + small_cos) + (min_sin + small_sin) * (min_sin * small_sin));
					}
				}
			}
		}
	}
}

bool Enemy::eaten(Cell* cell) {
	return Cell::eaten(cell);
}