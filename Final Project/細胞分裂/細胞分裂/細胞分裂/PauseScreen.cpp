#include "PauseScreen.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "constant.h"
//#include <iostream>
//using namespace std;

void PauseScreen::draw(SDL_Renderer* r) {
	boxColor(r, 0, 0, WIDTH, HEIGHT, 0xAAFF11AA);
	roundedBoxColor(r, WIDTH / 6, HEIGHT / 2, WIDTH * 5 / 6, HEIGHT / 2 + 20, 5, 0xAAFFAAAA);
	roundedBoxColor(r, WIDTH / 6, HEIGHT * 5 / 6, WIDTH * 5 / 6, HEIGHT * 5 / 6 + 20, 5, 0xAAFFAAAA);
	aaFilledEllipseColor(r, music * WIDTH * 4 / 6.0 / MaxVolume + WIDTH / 6.0, HEIGHT / 2.0 + 10, 40, 40, 0xAAFFAAFF);
	aaFilledEllipseColor(r, audio * WIDTH * 4 / 6.0 / MaxVolume + WIDTH / 6.0, HEIGHT * 5 / 6.0 + 10, 40, 40, 0xAAFFAAFF);
}

void PauseScreen::setVolume(int x, int y) {
	if (y > HEIGHT / 3 && y <= HEIGHT * 2 / 3) {
		if (x < WIDTH / 6) {
			music = 0;
		}
		else if (x > WIDTH * 5 / 6) {
			music = MaxVolume;
		}
		else {
			music = (x - WIDTH / 6) / (WIDTH * 4 / 6 / MaxVolume);
		}
	}
	else if (y > HEIGHT * 2 / 3 && y <= HEIGHT) {
		if (x < WIDTH / 6) {
			audio = 0;
		}
		else if (x > WIDTH * 5 / 6) {
			audio = MaxVolume;
		}
		else {
			audio = (x - WIDTH / 6) / (WIDTH * 4 / 6 / MaxVolume);
		}
	}
	//cout << "Audio:" << audio << endl;
	//cout << "Music:" << music << endl;

}

int PauseScreen::getMusic() const
{ return music; }
int PauseScreen::getAudio() const
{ return audio; }