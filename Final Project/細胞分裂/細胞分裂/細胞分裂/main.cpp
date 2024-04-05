#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include "SDL_ttf.h"
#include <SDL_image.h>
#include "constant.h"
#include "RenderWindow.h"
#include "Image.h"
#include "Player.h"
#include "PlayerSplit.h"
#include "Enemy.h"
#include "Boss.h"
#include "Screen.h"
#include "PauseScreen.h"
#include "AminoAcid.h"
#include "AntiAminoAcid.h"
#include "Canon.h"

/************************/
/* New in this example */
#include "System.h"  // Timer
#include "StaticRole.h"
#include "AnimeRole.h"
#include "Text.h"
#include "Mixer.h"
/***********************/

std::vector<Player*> cells(1);
std::vector<Enemy*> enemies;
std::vector<Canon*> canons; 
Screen screen(BeginX, BeginY);//generate map
Cell* PlayerSplit::player = NULL;
int center = 0;//default player view
int Cell::STATE = START;

struct keyBoard
{
	bool up;
	bool left;
	bool down;
	bool right;
	bool w;
	bool a;
	bool s;
	bool d;
	bool shift;
} KB;

struct Mouse
{
	MouseState state;
	int x;
	int y;
} M;

void HandleStartKeyboardEvent(SDL_Event& e);
//void HandleStartMouseEvent(SDL_Event& e);
void HandleActiveKeyboardEvent(SDL_Event& e);
void HandlePauseKeyboardEvent(SDL_Event& e);
void HandlePauseMouseEvent(SDL_Event* e, Mouse* m);

void generateEnemy(int&, int&);
void generateCanon();

// When using SDL, you have to use "int main(int argc, char* args[])"
// int main() and void main() are not allowed
int main(int argc, char* args[])
{
	System sdl;
	// Start up SDL and create window
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	
	int i, j;

	Mixer e1("../audio/bubbleeffect.wav", EFFECT);
	Mixer e2("../audio/eatingsoundeffect.wav", EFFECT);
	Mixer e3("../audio/hitwalleffect.wav", EFFECT);
	Mixer e4("../audio/hurtsoundeffect.wav", EFFECT);
	Mixer e5("../audio/dooropensoundeffect.wav", EFFECT);
	Mixer m1("../audio/bgm.mp3", MUSIC);

	RenderWindow window("Cell Division", 20, 20, WIDTH, HEIGHT);

	PauseScreen Pscreen;
	SDL_RendererFlip no = SDL_FLIP_NONE;
	SDL_RendererFlip ho = SDL_FLIP_HORIZONTAL;
	SDL_RendererFlip ve = SDL_FLIP_VERTICAL;
	SDL_RendererFlip hove = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

	bool winning = 0;

	bool eaten;
	cells[0] = new Player(BeginX, BeginY, 0, 0, McSize, screen, PlayerSplit::player);
	PlayerSplit::player = cells[0]; //set static Player*, when split meet player, don't consider the size, just eat the split
	PlayerSplit* split;// resources for split
	int Time = 0;

	generateCanon();

	Boss* boss = NULL; // resources for enemies
	int bossNum = 0, enemyNum = 0;
	generateEnemy(enemyNum, bossNum);
	double min, small, ally;
	Cell *min_cell, *small_cell, *ally_cell;
	bool ChaseAndRun;

	AminoAcid* amino[50] = { NULL }; // resources for aminoacid
	for (i = 0; i < 50; i++)
	{
		amino[i] = new AminoAcid();
		amino[i]->generateAmino(screen, cells[0]);
	}

	//Text textshaded("Shaded: WHO cares!!!", "../fonts/lazy.ttf", 40, TTF_STYLE_BOLD, { 250, 20, 240 }, SHADED, { 17, 253, 40 }, window.getRenderer(), { 100, 300 }, { 10, 10 }, 30, no, 255);

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		switch (Cell::STATE)
		{
		case START:

			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				// Handle input for the dot
				HandleStartKeyboardEvent(e);
				//HandleStartMouseEvent(&e, &M);
			}

			break;

		case ACTIVE:

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				// Handle input for the dot
				HandleActiveKeyboardEvent(e);
			}

			screen.setP(cells[center]->getPX(), cells[center]->getPY());

			// Player
			eaten = 0;
			cells[0]->runMC(KB.up, KB.down, KB.left, KB.right);
			cells[0]->move();
			cells[0]->setDif(screen);
			cells[0]->hitWall(screen);
			cells[0]->resistance();
			if (cells[0]->ishitwall()) e3.playEffect(0, -1);

			for (i = 0; i < enemies.size(); i++) {
				if (cells[0]->eaten(enemies[i]))// mc eaten by enemies
				{
					e2.playEffect(0, -1);
					printf("you're dead!\n");
					eaten = 1;
				}
			}
			if (eaten) {
				winning = 0; 
				Cell::STATE = FINISH;
			}
			//PlayerSplit
			if (cells.size() > 1)
			{
				for (i = 1; i < cells.size(); i++)
				{
					eaten = 0;
					split = dynamic_cast<PlayerSplit*>(cells[i]);

					split->runSplit(KB.w, KB.s, KB.a, KB.d);
					cells[i]->move();
					cells[i]->setDif(screen);
					cells[i]->hitWall(screen);
					cells[i]->resistance();

					// cells eaten by cells
					if (split->getT() > 1000)
					{
						for (j = 0; j < cells.size(); j++) {
							if (i == j) continue;
							if (cells[i]->eaten(cells[j])) {
								eaten = 1;
								delete cells[i];
								cells.erase(cells.begin() + i--);
								center = 0;
								e2.playEffect(0, -1);
							}
						}
					}//edible now
					else split->setT();
					if (eaten) continue;

					// cells eaten by viruses
					for (j = 0; j < enemies.size(); j++) {
						if (cells[i]->eaten(enemies[j])) {
							eaten = 1;
							delete cells[i];
							cells.erase(cells.begin() + i--);
							center = 0;
							e2.playEffect(0, -1);
						}
					}
					if (eaten) continue;
				}
			}

			//Enemies
			if (enemies.size())
			{
				for (i = 0; i < enemies.size(); i++) {
					//boss = dynamic_cast<Boss*>(enemies[i]);

					ChaseAndRun = 0;
					eaten = 0;
					min_cell = NULL;
					small_cell = NULL;
					ally_cell = NULL;
					enemies[i]->move();
					enemies[i]->setDif(screen);
					enemies[i]->hitWall(screen);

					ally = min = small = 2 * Hypotenuse;

					// viruses eaten by viruses
					for (j = 0; j < enemies.size(); j++) {
						if (i == j) continue;
						/*if (i < bossNum) {
							if (boss->eaten(enemies[j], screen)) {
								eaten = 1;
								delete enemies[i];
								enemies.erase(enemies.begin() + i--);
								break;
							}
						}
						else {*/
							if (enemies[i]->eaten(enemies[j])) {
								eaten = 1;
								delete enemies[i];
								enemies.erase(enemies.begin() + i--);
								break;
							}
						//}
						
						
						if (ally > enemies[i]->getDis()) ally = enemies[i]->getDis(), ally_cell = enemies[j];
					}
					if (eaten) continue;

					// viruses eaten by cells
					for (j = 0; j < cells.size(); j++) {
						/*if (i < bossNum) {
							if (boss->eaten(cells[j], screen)) {
								eaten = 1;
								delete enemies[i];
								enemies.erase(enemies.begin() + i--);
								break;
							}
						}
						else {*/
							if (enemies[i]->eaten(cells[j])) {
								eaten = 1;
								delete enemies[i];
								enemies.erase(enemies.begin() + i--);
								e2.playEffect(0, -1);
								break;
							}
						//}
						
						if (!j && enemies[i]->getDis() < 2 * Hypotenuse) ChaseAndRun = 1;
						if (min > enemies[i]->getDis()) min = enemies[i]->getDis(), min_cell = cells[j];
						if (enemies[i]->getDis() < 2 * Hypotenuse && cells[j]->getR() < small) small = cells[j]->getR(), small_cell = cells[j];
					}
					if (eaten) continue;

					if (ChaseAndRun) {
						enemies[i]->ChaseAndRun(min_cell, small_cell, ally_cell);
					}
					//if (i < bossNum) boss->Attack(min_cell, screen, cells);
				}
			}

			for (i = 0; i < 50; i++)//AminoAcid
			{
				amino[i]->setDif(screen);
				for (j = 0; j < cells.size(); j++) {// cells eat amino
					if (amino[i]->eaten(cells[j]))
					{
						amino[i]->generateAmino(screen, cells[0]);
						e1.playEffect(0, -1);
					}
				}
				for (j = 0; j < enemies.size(); j++) {// enemies eat amino
					if (amino[i]->eaten(enemies[j])) amino[i]->generateAmino(screen, cells[0]);
				}
				if (amino[i]->getDif() > Hypotenuse) // amino out of screen
					amino[i]->generateAmino(screen, cells[0]);
			}

			if (canons.size()) {
				for (i = 0; i < canons.size(); i++) {
					min_cell = NULL;
					min = 2 * Hypotenuse;
					canons[i]->setDif(screen);
					for (j = 0; j < cells.size(); j++) {
						canons[i]->setDis(cells[j]);
						if (canons[i]->getDis() < min) min = canons[i]->getDis(), min_cell = cells[j];
						if (canons[i]->eaten(cells[j])) e4.playEffect(0, -1);
					}
					if (min_cell) {
						canons[i]->AimAndShoot(min_cell);
					}
					canons[i]->recollect(screen, cells);
					
				}
			}
			if (!enemies.size() && !winning) {
				screen.setEnd();
				winning = 1;
				e5.playEffect(0, -1);
				printf("------------\n");
				printf("GATE OPEN!!!\n");
				printf("------------\n");
			}
			if (cells[0]->getPX() > EndX && cells[0]->getPY() > EndY) Cell::STATE = FINISH;

			if (!m1.isPlaying()) // If there is no music playing
			{
				m1.play(0); // Play the music								
			}

			break;

		case PAUSE:

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				// Handle input for the dot
				HandlePauseKeyboardEvent(e);
				HandlePauseMouseEvent(&e, &M);
			}
			switch (M.state)
			{
			case NONE: break;
			case OUT: break; // Mouse out
			/*case IN_LB_SC:  // Inside, Left Button, Single Click
				printf("Inside, Left Button, Single Click: (%d, %d)\n", M.x, M.y);
				break;

			case IN_RB_SC:  // Inside, RIGHT Button, Single Click
				printf("Inside, Right Button, Single Click: (%d, %d)\n", M.x, M.y);
				break;

			case IN_LB_DC:  // Inside, Left Button, Double Click
				printf("Inside, Left Button, Double Click: (%d, %d)\n", M.x, M.y);
				break;

			case IN_RB_DC:  // Inside, RIGHT Button, Double Click
				printf("Inside, Right Button, Double Click: (%d, %d)\n", M.x, M.y);
				break;

			case IN_LB_PR:  // Inside, Left Button, Press
				printf("Inside, Left Button, Press: (%d, %d)\n", M.x, M.y);
				break;

			case IN_RB_PR:  // Inside, Right Button, Press
				printf("Inside, Right Button, Press: (%d, %d)\n", M.x, M.y);
				break;

			case IN_WU:  // Inside, Wheel UP
				printf("Inside, Wheel Up: y=%d\n", M.y);
				break;

			case IN_WD:  // Inside, Wheel DOWN
				printf("Inside, Wheel Down: y=%d\n", M.y);
				break;

			case HOVER: // Mouse hover
				printf("Inside, Hover: (%d, %d)\n", M.x, M.y);
				break;
*/
			case IN_LB_PR_HOVER: // Mouse hover
				Pscreen.setVolume(M.x, M.y);
				m1.setVolume(Pscreen.getMusic());
				e1.setVolume(Pscreen.getAudio());
				break;
			case IN_RB_PR_HOVER: // Mouse hover
				Pscreen.setVolume(M.x, M.y);
				m1.setVolume(Pscreen.getMusic());
				e1.setVolume(Pscreen.getAudio());
				break;
			}

			break;

		case FINISH:

			if (winning) printf("you won");
			else printf("you lose");

			window.close();
			sdl.close();
			return 0;
			break;

		default:
			break;
		}

		// Clear screen
		window.clear();
		
		screen.draw(window.getRenderer());
		for (i = 0; i < 50; i++) amino[i]->draw(window.getRenderer());
		for (i = 0; i < enemies.size(); i++) enemies[i]->draw(window.getRenderer());
		for (i = 0; i < cells.size(); i++) cells[i]->draw(window.getRenderer());
		for (i = 0; i < canons.size(); i++) canons[i]->draw(window.getRenderer());
		//textshaded.draw();
		if (Cell::STATE == PAUSE) Pscreen.draw(window.getRenderer());
		else if (Cell::STATE == START) boxRGBA(window.getRenderer(), 0, 0, WIDTH, HEIGHT, 100, 100, 100, 100);
		// Update screen
		window.display();
	}

	e1.close();
	e2.close();
	e3.close();
	e4.close();
	e5.close();
	m1.close();
	//Free resources and close SDL
	window.close();
	sdl.close();
	
	return 0;
}

void generateEnemy(int& enemyNum, int& bossNum) {
	int side;
	Enemy* tmp;
	for (int i = 1; i < MAX_MAZE - 1; i++) {
		for (int j = 1; j < MAX_MAZE - 1; j++) {
			if (i == BeginX / width && j == BeginY / height) continue;
			side = 0;
			if (!screen.getMaze(i * width, j * height)) {
				if (i > 1 && screen.getMaze((i - 1) * width, j * height)) side++;
				if (j > 1 && screen.getMaze(i * width, (j - 1) * height)) side++;
				if (i < MAX_MAZE - 1 && screen.getMaze((i + 1) * width, j * height)) side++;
				if (j < MAX_MAZE - 1 && screen.getMaze(i * width, (j + 1) * height)) side++;
				if (side == 2) {
					if (!(rand() % (int)(1 / EnemyPercentage))) {
						enemies.push_back(new Enemy(i * width + width / 2, j * height + height / 2, 0, 0, EnemySize, screen, cells[0]));
						enemyNum++;
					}
				}
				/*else if (side == 3) {
					enemies.push_back(new Boss(i * width + width / 2, j * height + height / 2, 0, 0, BossSize, screen, cells[0]));
					tmp = enemies[bossNum];
					enemies[bossNum] = enemies[enemies.size() - 1];
					enemies[enemies.size() - 1] = tmp;
					bossNum++;
				}*/
			}
		}
	}
}

void generateCanon() {
	for (int i = 1; i < MAX_MAZE - 1; i++) {
		for (int j = 1; j < MAX_MAZE - 1; j++) {

			if (i == BeginX / width && j == BeginY / height) continue;
			if (!screen.getMaze(i * width, j * height)) {
				if (i < MAX_MAZE - 1 && screen.getMaze((i + 1) * width, j * height)) {
					if (!(rand() % (int)(1 / CanonPercentage))) {
						canons.push_back(new Canon((i + 1) * width, (j + 0.5) * height, screen, -1, 0));
					}
				}
				if (i > 1 && screen.getMaze((i - 1) * width, j * height)) {
					if (!(rand() % (int)(1 / CanonPercentage))) {
						canons.push_back(new Canon(i * width, (j + 0.5) * height, screen, 1, 0));
					}
				}
				if (j < MAX_MAZE - 1 && screen.getMaze(i * width, (j + 1) * height)) {
					if (!(rand() % (int)(1 / CanonPercentage))) {
						canons.push_back(new Canon((i + 0.5) * width, (j + 1) * height, screen, 0, -1));
					}
				}
				if (j > 1 && screen.getMaze(i * width, (j - 1) * height)) {
					if (!(rand() % (int)(1 / CanonPercentage))) {
						canons.push_back(new Canon((i + 0.5) * width, j * height, screen, 0, 1));
					}
				}
			}
		}
	}
}

void HandleStartKeyboardEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE: Cell::STATE = PAUSE; break;
		default: Cell::STATE = ACTIVE; break;
		}
	}
}

void HandleActiveKeyboardEvent(SDL_Event& e)
{	/* The method for "Debunce" */

	// If a key was pressed
	// repeat: non-zero if this is a key repeat
	// https://wiki.libsdl.org/SDL_KeyboardEvent
	//if (e.type == SDL_KEYDOWN)

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:    if (!KB.up) KB.up = 1; break;
		case SDLK_DOWN:  if (!KB.down) KB.down = 1; break;
		case SDLK_LEFT:  if (!KB.left) KB.left = 1; break;
		case SDLK_RIGHT: if (!KB.right) KB.right = 1; break;
		case SDLK_SPACE:
			if (cells.size() < MAX_SPLIT && cells[0]->getR() > 5) {
				cells.push_back(new PlayerSplit(cells[0]->getPX(), cells[0]->getPY(), cells[0]->getVX() * cells[0]->getVX() / cells[0]->getV() * -1, cells[0]->getVY() * cells[0]->getVY() / cells[0]->getV() * -1, cells[0]->getR() / sqrt(2), screen));
				cells[0]->setVX(cells[0]->getVX() + -1 * cells[cells.size() - 1]->getVX());
				cells[0]->setVY(cells[0]->getVY() + -1 * cells[cells.size() - 1]->getVY());
				cells[0]->setR(cells[0]->getR() / sqrt(2));
			}
			break;
		case SDLK_w: if (!KB.w) KB.w = 1; break;
		case SDLK_a: if (!KB.a) KB.a = 1; break;
		case SDLK_s: if (!KB.s) KB.s = 1; break;
		case SDLK_d: if (!KB.d) KB.d = 1; break;
		case SDLK_1: if (cells.size() > 1) center = 1; break;
		case SDLK_2: if (cells.size() > 2) center = 2; break;
		case SDLK_3: if (cells.size() > 3) center = 3; break;
		case SDLK_4: if (cells.size() > 4) center = 4; break;
		case SDLK_5: if (cells.size() > 5) center = 5; break;
		case SDLK_6: if (cells.size() > 6) center = 6; break;
		case SDLK_7: if (cells.size() > 7) center = 7; break;
		case SDLK_8: if (cells.size() > 8) center = 8; break;
		case SDLK_9: if (cells.size() > 9) center = 9; break;
		case SDLK_ESCAPE: Cell::STATE = PAUSE; break;
		}
	}

	//If a key was released
	//else if (e.type == SDL_KEYUP)
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:    if (KB.up) KB.up = 0; break;
		case SDLK_DOWN:  if (KB.down) KB.down = 0; break;
		case SDLK_LEFT:  if (KB.left) KB.left = 0; break;
		case SDLK_RIGHT: if (KB.right) KB.right = 0; break;
		case SDLK_w: if (KB.w) KB.w = 0; break;
		case SDLK_a: if (KB.a) KB.a = 0; break;
		case SDLK_s: if (KB.s) KB.s = 0; break;
		case SDLK_d: if (KB.d) KB.d = 0; break;
		case SDLK_1: center = 0; break;
		case SDLK_2: center = 0; break;
		case SDLK_3: center = 0; break;
		case SDLK_4: center = 0; break;
		case SDLK_5: center = 0; break;
		case SDLK_6: center = 0; break;
		case SDLK_7: center = 0; break;
		case SDLK_8: center = 0; break;
		case SDLK_9: center = 0; break;
		}
	}
}

void HandlePauseKeyboardEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE: Cell::STATE = ACTIVE; break;
		}
	}
}

void HandlePauseMouseEvent(SDL_Event* e, Mouse* m)
{
	// If mouse event happened
	// https://wiki.libsdl.org/SDL_Event
	// https://wiki.libsdl.org/SDL_MouseMotionEvent
	// https://wiki.libsdl.org/SDL_MouseButtonEvent
	// https://wiki.libsdl.org/SDL_MouseWheelEvent
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL)
	{
		// Get mouse position
		// https://wiki.libsdl.org/SDL_GetMouseState		
		SDL_GetMouseState(&(m->x), &(m->y));
		//printf("(%d, %d)\n", *x, *y);

		static int lasttime = SDL_GetTicks64();
		static int curtime = SDL_GetTicks64();
		int timediv;

		lasttime = curtime;
		curtime = SDL_GetTicks64();
		timediv = curtime - lasttime;

		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			break;

		case SDL_MOUSEBUTTONUP:
			if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 2 && timediv < 150) m->state = IN_LB_DC;
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 2 && timediv < 150) m->state = IN_RB_DC;
			else if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 1 && timediv < 800 && timediv > 100) m->state = IN_LB_SC;
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 1 && timediv < 800 && timediv > 100) m->state = IN_RB_SC;

			break;

		case SDL_MOUSEWHEEL:
			if (e->wheel.y > 0) // scroll up
			{
				// Put code for handling "scroll up" here!
				m->y = e->wheel.y;
				m->state = IN_WU;
			}
			else if (e->wheel.y < 0) // scroll down
			{
				// Put code for handling "scroll down" here!
				m->y = e->wheel.y;
				m->state = IN_WD;
			}
			break;

		case SDL_MOUSEMOTION:
			m->state = HOVER;
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				m->state = IN_LB_PR_HOVER;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT) {
				m->state = IN_RB_PR_HOVER;
			}
			break;
		}
	}
}
