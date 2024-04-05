#pragma once
#include "PlayerSplit.h"
#include <stdlib.h>
class AntiAminoAcid
{
	public:
		AntiAminoAcid() { PX = 0, PY = 0, DifX = 0, DifY = 0, radius = AminoAcidSize; }
		AntiAminoAcid(double px, double py, double r);
		double getPX();
		double getPY();
		void setP(double, double);
		void setV(double, double);
		void setDif(Screen& screen);
		void move();
		void draw(SDL_Renderer* r); // Draw
		bool eaten(Cell*);
		friend void operator-=(Cell* cell, AntiAminoAcid& anti);
	private:
		double PX;
		double PY;
		double VX = 0;
		double VY = 0;
		double DifX;
		double DifY;
		double radius;
};

