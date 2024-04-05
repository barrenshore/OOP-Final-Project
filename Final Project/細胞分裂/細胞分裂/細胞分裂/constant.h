#pragma once

//Screen dimension constants
const int WIDTH = 960;//800
const int HEIGHT = 540;//600
const int width = WIDTH / 6 * 4;//640
const int height = HEIGHT / 6 * 4;//360

const int Hypotenuse = (int)sqrt(width* width + height * height);
const int McSize = 20;
const int EnemySize = 30;
const int BossSize = 20;
const int AminoAcidSize = 5;

const int CanonSize = 30;
const int BulletCount = 10;
const int BarrelSize = CanonSize + 20;
const int BulletVelocity = 5;

const int VELOCITY = 10;
const int SplitVelocity = 10;
const int EnemyVelocity = (int)sqrt(2);//10;
const int BossVelocity = (int)sqrt(2);

const int MAX_SPLIT = 5;
const int MAX_MAZE = 7;
const int MaxVolume = 128;

const int BeginX = width * 3 / 2;
const int BeginY = height * 3 / 2;
const int EndX = width * (MAX_MAZE - 1);
const int EndY = height * (MAX_MAZE - 2);

const double EnemyPercentage = 0.2;
const double CanonPercentage = 0.2;

#define START -1
#define PAUSE 0
#define ACTIVE 1
#define FINISH 2

//Screen dimension constants
#define ALLREGION -1
#define SOLID 100
#define SHADED 101
#define BLENDED 102
#define MUSIC 10
#define EFFECT 11

enum MouseState
{
	NONE = 0,
	OUT = 1, // Mouse out
	IN_LB_SC = 2,  // Inside, Left Button, Single Click
	IN_RB_SC = 3,  // Inside, RIGHT Button, Single Click
	IN_LB_DC = 4,  // Inside, Left Button, Double Click
	IN_RB_DC = 5,  // Inside, RIGHT Button, Double Click
	IN_LB_PR = 6,  // Inside, Left Button, Press
	IN_RB_PR = 7,  // Inside, Left Button, Press
	IN_WU = 8,  // Inside, Wheel UP
	IN_WD = 9,  // Inside, Wheel DOWN
	HOVER = 10, // Mouse hover
	IN_LB_PR_HOVER = 11, // Inside, Left Button, Press, Hover
	IN_RB_PR_HOVER = 12 // Inside, Left Button, Press, Hover
};