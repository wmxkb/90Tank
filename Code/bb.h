#pragma once
#include<graphics.h>

#define SPEED 10
class BB {
private:
	IMAGE* zd;
	int* x;
	int* y;
	int sx;
	int sy;
	int w, h;
	int* dir;
	bool* life;
	int num;
	int* id;
public:
	BB() {
		sx = 1;
		sy = 171;
		w = 6;
		h = 8;
		zd = new IMAGE();
		loadimage(zd, L"tk.png");
		x = new int[2000];
		y = new int[2000];
		life = new bool[2000];
		id = new int[2000];
		num = 0;
		dir = new int[2000];
		for (int i = 0; i < 2000; ++i) {
			dir[i] = 0;
			x[i] = 0;
			y[i] = 0;
			life[i] = true;
		}
	}

	int GetId(int i) {
		return id[i];
	}
	int GetX(int i) {
		return x[i];
	}

	int GetY(int i) {
		return y[i];
	}
	int GetNum() {
		return num;
	}
	int GetDir(int i) {
		return dir[i];
	}
	void  add(int x, int y, int dir, int k) {
		this->x[num] = x;
		this->y[num] = y;
		this->dir[num] = dir;
		id[num] = k;
		++num;
	}
	void setLifeFalse(int i) {
		life[i] = false;
	}
	bool getLife(int i) {
		return life[i];
	}
	void bbShow() {
		for (int i = 0; i < num; ++i) {
			if (x[i] < 0 || x[i] > 462 || y[i] < 0 || y[i] > 472)
				life[i] = false;

			switch (dir[i]) {
			case 0:
				sx = 1;
				sy = 171;
				w = 6;
				h = 8;
				y[i] -= SPEED;
				break;
			case 1:
				sx = 1;
				sy = 181;
				w = 8;
				h = 6;
				x[i] -= SPEED;
				break;
			case 2:
				sx = 11;
				sy = 171;
				w = 6;
				h = 8;
				y[i] += SPEED;
				break;
			case 3:
				sx = 11;
				sy = 181;
				w = 8;
				h = 6;
				x[i] += SPEED;
				break;

			}
			if (life[i])
				putimage(x[i], y[i], w, h, zd, sx, sy);
		}

	}

};
