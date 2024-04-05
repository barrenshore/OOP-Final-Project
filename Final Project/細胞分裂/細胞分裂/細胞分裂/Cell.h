#pragma once
#include <stdio.h>
#include "Screen.h"
class Cell
{
	public:
		Cell(double x, double y, double vx, double vy, double r, Screen& screen, Cell* cell);
		virtual ~Cell() { printf("\tCell is destroyed\n"); }
		double getPX() const;
		double getPY() const;
		void setPX(double x);
		void setPY(double y);
		double getVX() const;
		double getVY() const;
		double getV() const;
		void setVX(double x);
		void setVY(double y);
		double getR() const;
		void setR(double r);

		virtual void setDif(Screen& screen);

		virtual void setDis(Cell*);
		double getDisX() const;
		double getDisY() const;
		double getDis() const;
		bool ishitwall() const;

		void resistance();
		void hitWall(Screen&);
		void move();

		virtual void draw(SDL_Renderer* r) = 0;
		virtual bool eaten(Cell* cell);

		static int STATE;
	protected:
		// offsets
		double mPosX = BeginX;
		double mPosY = BeginY;
		double radius;

		// velocity
		double mVelX;
		double mVelY;
		
		// from the center of the screen
		double mDifX;
		double mDifY;
		
		// distance with the cell which will eat it 
		double mDisX;
		double mDisY;
		double mDis;

		bool hitwall;
};

