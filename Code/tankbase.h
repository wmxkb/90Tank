#pragma once
#include<graphics.h>
#include"wall.h"
#include"bb.h"
#include<ctime>
class tank {

private:
	IMAGE *tankinit;
	int x;										//坦克坐标
	int y;
	int sx;										//坦克在图片实际坐标
	int sy;
	int w;
	int h;
	int speed;									//坦克速度
	int dir;									//方向
	int tempt;									//标记时间
	bool flagw, flaga, flags, flagd;			//方向标记，用于2帧图片播放
	bool life;
	int loss;


public:

	int id;
	tank();
	void Setloss(int i) {
		loss = i;
	}
	int Getloss() { return loss; }
	void setXY(int x, int y) { this->x = x; this->y = y; }
	void setSpeed(int speed);					//设置坦克移动速度
	int getDir() { return dir; }
	void setDir(int i) { dir = i; }
	int getX() { return x; }					//获取x
	int getY() { return y; }					//获取y
	void setSxy(int x, int y) { sx = x; sy = y; }
	bool getLife() { return life; }
	void setLife(bool l) {
		life = l;
	}

	int move(BB* b, int CountT, bool t);			//坦克移动,开炮函数
	int move(BB* b, int CountT, bool t, int * music);
	void setMove(bool t, int d, int CountT, BB*b);						//手动设定移动方向
	void setMove(bool t, int CountT, BB* b);
	//void bb(BB* b);							//坦克开炮
	void caseHit(BB* b, int k, int* music);

	void show() {								//显示坦克
		if (life) {
			putimage(x, y, w, h, tankinit, sx, sy);

		}
		else {
			if (id) {
				loss++;
				life = true;
				x = 150;
				y = 448;
				w = 26;
				h = 32;
				sx = 276;
				sy = 35;
				putimage(x, y, w, h, tankinit, sx, sy);
			}
		}

	}

};

class AI :public tank {
public:
	static int beataisum;
	AI() {
		setXY(2, 2);
		setSxy(38, 308);
		setLife(1);
	}
	void move(BB* b, int CountT, bool t, unsigned int n) {
		id = 0;

		setMove(t, n, CountT, b);
	}
	void move(BB* b, int CountT, bool t) {
		id = 0;

		setMove(t, CountT, b);
	}

};

