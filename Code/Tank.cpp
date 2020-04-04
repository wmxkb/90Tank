#include "tankbase.h"
#include<graphics.h>
#include<conio.h>
#include"wall.h"
#include"bb.h"
#include<Windows.h>
#include<Mmsystem.h>
#include<iostream>
#pragma comment(lib,"Winmm.lib")
int AI::beataisum = 0;
tank::tank() {
	loss = 0;
	dir = 2;
	x = 150;
	y = 454;
	w = h = 26;
	sx = 4;
	sy = 38;
	speed = 10;
	tempt = 0;
	flagw = flaga = flags = flagd = true;
	life = true;
	id = 1;
	tankinit = new IMAGE();
	loadimage(tankinit, L"tk.png");


}
void tank::setSpeed(int speed) {
	this->speed = speed;
}

void tank::caseHit(BB* b, int k, int*music) {

	for (int j = 0; j < b->GetNum(); ++j) {
		if (k != b->GetId(j)) {
			if (b->getLife(j)) {
				switch (b->GetDir(j)) {
				case 0:
					if (b->GetX(j) + 6 > x && b->GetX(j) <= x + 26 && b->GetY(j) > y - 8 && b->GetY(j) <= y + 26) {
						*music = 3;
						//PlaySoundW(TEXT("kill.wav"), NULL, SND_FILENAME | SND_SYNC);//同步播放方式
						life = false;

						b->setLifeFalse(j);
					}
					break;
				case 1:
					if (b->GetX(j) > x - 8 && b->GetX(j) <= x + 26 && b->GetY(j) + 6 > y && b->GetY(j) <= y + 26) {
						*music = 3;
						//PlaySoundW(TEXT("kill.wav"), NULL, SND_FILENAME | SND_SYNC);
						life = false;

						b->setLifeFalse(j);
					}
					break;
				case 2:
					if (b->GetX(j) + 6 > x && b->GetX(j) <= x + 26 && b->GetY(j) > y - 8 && b->GetY(j) <= y + 26) {
						*music = 3;
						//PlaySoundW(TEXT("kill.wav"), NULL, SND_FILENAME | SND_SYNC);
						life = false;

						b->setLifeFalse(j);

					}
					break;
				case 3:
					if (b->GetX(j) > x - 8 && b->GetX(j) <= x + 26 && b->GetY(j) + 6 > y && b->GetY(j) <= y + 26) {
						*music = 3;
						//PlaySoundW(TEXT("kill.wav"), NULL, SND_FILENAME | SND_SYNC);
						life = false;

						b->setLifeFalse(j);
					}
					break;
				}
			}
		}

	}
}

int tank::move(BB* b, int CountT, bool t) {//坦克移动，2帧
	//char msg;
	int returni = 0;
	if (t) {//不够完美


		if (GetAsyncKeyState(38) & 0x8000) {

			dir = 0;
			y -= speed;
			if (flagw) {
				sx = 4;
				sy = 38;
				flagw = false;
			}
			else {
				sx = 38;
				sy = 38;
				flagw = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(37) & 0x8000) {

			dir = 1;
			x -= speed;
			if (flaga) {
				sx = 208;
				sy = 38;
				flaga = false;
			}
			else {
				sx = 242;
				sy = 38;
				flaga = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(40) & 0x8000) {

			dir = 2;
			y += speed;
			if (flags) {
				sx = 140;
				sy = 38;
				flags = false;
			}
			else {
				sx = 174;
				sy = 38;
				flags = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(39) & 0x8000) {

			dir = 3;
			x += speed;
			if (flagd) {
				sx = 72;
				sy = 38;
				flagd = false;
			}
			else {
				sx = 106;
				sy = 38;
				flagd = true;
			}
			returni = 1;
		}
		//	using namespace std;
		if (GetAsyncKeyState(32) & 0x8000) {
			if (CountT - tempt > 12) {
				tempt = CountT;
				switch (dir) {
				case 0:

					b->add(x + 10, y, dir, 1);
					break;
				case 1:
					b->add(x, y + 10, dir, 1);
					break;
				case 2:
					b->add(x + 10, y + 18, dir, 1);
					break;
				case 3:
					b->add(x + 18, y + 10, dir, 1);
					break;
				}

			}

		}

		/*
		if (_kbhit()) {
			msg = _getch();
			switch (msg) {
			case 'w':
			case 'W':
				dir = 0;
				y -= speed;
				if (flagw) {
					sx = 4;
					sy = 38;
					flagw = false;
				}
				else {
					sx = 38;
					sy = 38;
					flagw = true;
				}

				break;
			case 'a':
			case 'A':
				dir = 1;
				x -= speed;
				if (flaga) {
					sx = 208;
					sy = 38;
					flaga = false;
				}
				else {
					sx = 242;
					sy = 38;
					flaga = true;
				}
				break;
			case 's':
			case 'S':
				dir = 2;
				y += speed;
				if (flags) {
					sx = 140;
					sy = 38;
					flags = false;
				}
				else {
					sx = 174;
					sy = 38;
					flags = true;
				}
				break;
			case 'd':
			case 'D':
				dir = 3;
				x += speed;
				if (flagd) {
					sx = 72;
					sy = 38;
					flagd = false;
				}
				else {
					sx = 106;
					sy = 38;
					flagd = true;
				}
				break;
			case 32:
				b->add(x + 13, y, dir);
				switch (dir) {
				case 0:
					y -= speed;
					break;
				case 1:
					x -= speed;
					break;
				case 2:
					y += speed;
					break;
				case 3:
					x += speed;
					break;
				default:
					break;
				}

				break;
			}

		}
	*/
	}
	else {
		switch (dir) {
		case 0:
			y += speed;
			break;
		case 1:
			x += speed;
			break;
		case 2:
			y -= speed;
			break;
		case 3:
			x -= speed;
			break;
		default:
			break;
		}
	}

	return returni;


}
int tank::move(BB* b, int CountT, bool t, int*music) {//坦克移动，2帧
	//char msg;
	int returni = 0;
	if (t) {//不够完美

		*music = 2;
		/*if (CountT - tempt > 15) {
			switch (dir) {
			case 0:
				sx = 276;
				sy = 35;
				break;
			case 1:
				sx = 511;
				sy = 38;
				break;
			case 2:
				sx = 412;
				sy = 35;
				break;
			case 3:
				sx = 341;
				sy = 38;
				break;
			default:
				break;
			}
		}*/

		if (GetAsyncKeyState(38) & 0x8000) {
			w = 26;
			h = 26;
			*music = 0;
			dir = 0;
			y -= speed;
			if (flagw) {
				sx = 4;
				sy = 38;
				flagw = false;
			}
			else {
				sx = 38;
				sy = 38;
				flagw = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(37) & 0x8000) {
			w = 26;
			h = 26;
			*music = 0;
			dir = 1;
			x -= speed;
			if (flaga) {
				sx = 208;
				sy = 38;
				flaga = false;
			}
			else {
				sx = 242;
				sy = 38;
				flaga = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(40) & 0x8000) {
			w = 26;
			h = 26;
			*music = 0;
			dir = 2;
			y += speed;
			if (flags) {
				sx = 140;
				sy = 38;
				flags = false;
			}
			else {
				sx = 174;
				sy = 38;
				flags = true;
			}
			returni = 1;
		}
		else if (GetAsyncKeyState(39) & 0x8000) {
			h = 26;
			w = 26;

			*music = 0;
			dir = 3;
			x += speed;
			if (flagd) {
				sx = 72;
				sy = 38;
				flagd = false;
			}
			else {
				sx = 106;
				sy = 38;
				flagd = true;
			}
			returni = 1;
		}
		//	using namespace std;
		if (GetAsyncKeyState(32) & 0x8000) {
			if (CountT - tempt > 12) {
				*music = 1;
				tempt = CountT;
				switch (dir) {
				case 0:
					/*sx = 548;
					sy = 36;
					w = 26;
					h = 30;*/
					b->add(x + 10, y, dir, 1);
					break;
				case 1:
					b->add(x, y + 10, dir, 1);
					break;
				case 2:
					b->add(x + 10, y + 18, dir, 1);
					break;
				case 3:
					b->add(x + 18, y + 10, dir, 1);
					break;
				}

			}

		}
		/*
		if (_kbhit()) {
			msg = _getch();
			switch (msg) {
			case 'w':
			case 'W':
				dir = 0;
				y -= speed;
				if (flagw) {
					sx = 4;
					sy = 38;
					flagw = false;
				}
				else {
					sx = 38;
					sy = 38;
					flagw = true;
				}

				break;
			case 'a':
			case 'A':
				dir = 1;
				x -= speed;
				if (flaga) {
					sx = 208;
					sy = 38;
					flaga = false;
				}
				else {
					sx = 242;
					sy = 38;
					flaga = true;
				}
				break;
			case 's':
			case 'S':
				dir = 2;
				y += speed;
				if (flags) {
					sx = 140;
					sy = 38;
					flags = false;
				}
				else {
					sx = 174;
					sy = 38;
					flags = true;
				}
				break;
			case 'd':
			case 'D':
				dir = 3;
				x += speed;
				if (flagd) {
					sx = 72;
					sy = 38;
					flagd = false;
				}
				else {
					sx = 106;
					sy = 38;
					flagd = true;
				}
				break;
			case 32:
				b->add(x + 13, y, dir);
				switch (dir) {
				case 0:
					y -= speed;
					break;
				case 1:
					x -= speed;
					break;
				case 2:
					y += speed;
					break;
				case 3:
					x += speed;
					break;
				default:
					break;
				}

				break;
			}

		}
	*/
	}
	else {
		switch (dir) {
		case 0:
			y += speed;
			break;
		case 1:
			x += speed;
			break;
		case 2:
			y -= speed;
			break;
		case 3:
			x -= speed;
			break;
		default:
			break;
		}
	}

	return returni;


}

void tank::setMove(bool t, int d, int CountT, BB* b) {

	if (CountT - tempt > 12) {
		tempt = CountT;
		switch (dir) {
		case 0:
			b->add(x + 10, y, dir, 0);
			break;
		case 1:
			b->add(x, y + 10, dir, 0);
			break;
		case 2:
			b->add(x + 10, y + 18, dir, 0);
			break;
		case 3:
			b->add(x + 18, y + 10, dir, 0);
			break;
		}

	}

	if (t) {
		if (d == 0) {
			dir = 0;
			y -= speed;
			if (flagw) {
				sx = 4;
				sy = 308;
				flagw = false;
			}
			else {
				sx = 38;
				sy = 308;
				flagw = true;
			}
		}
		else if (d == 1) {
			dir = 1;
			x -= speed;
			if (flaga) {
				sx = 210;
				sy = 310;
				flaga = false;
			}
			else {
				sx = 244;
				sy = 310;
				flaga = true;
			}
		}
		else if (d == 2) {
			dir = 2;
			y += speed;
			if (flags) {
				sx = 140;
				sy = 308;
				flags = false;
			}
			else {
				sx = 174;
				sy = 308;
				flags = true;
			}
		}
		else if (d == 3) {
			dir = 3;
			x += speed;
			if (flagd) {
				sx = 70;
				sy = 310;
				flagd = false;
			}
			else {
				sx = 104;
				sy = 310;
				flagd = true;
			}
		}
	}
	else {
		switch (dir) {
		case 0:
			y += speed;
			break;
		case 1:
			x += speed;
			break;
		case 2:
			y -= speed;
			break;
		case 3:
			x -= speed;
			break;
		default:
			break;
		}
	}

}

void tank::setMove(bool t, int CountT, BB* b) {

	if (CountT - tempt > 20) {
		tempt = CountT;
		switch (dir) {
		case 0:
			b->add(x + 10, y, dir, 0);
			break;
		case 1:
			b->add(x, y + 10, dir, 0);
			break;
		case 2:
			b->add(x + 10, y + 18, dir, 0);
			break;
		case 3:
			b->add(x + 18, y + 10, dir, 0);
			break;
		}

	}

	if (t) {
		if (dir == 0) {
			y -= speed;
			if (flagw) {
				sx = 4;
				sy = 308;
				flagw = false;
			}
			else {
				sx = 38;
				sy = 308;
				flagw = true;
			}
		}
		else if (dir == 1) {
			x -= speed;
			if (flaga) {
				sx = 210;
				sy = 310;
				flaga = false;
			}
			else {
				sx = 244;
				sy = 310;
				flaga = true;
			}
		}
		else if (dir == 2) {
			y += speed;
			if (flags) {
				sx = 140;
				sy = 308;
				flags = false;
			}
			else {
				sx = 174;
				sy = 308;
				flags = true;
			}
		}
		else if (dir == 3) {
			x += speed;
			if (flagd) {
				sx = 70;
				sy = 310;
				flagd = false;
			}
			else {
				sx = 104;
				sy = 310;
				flagd = true;
			}
		}
	}
	else {
		switch (dir) {
		case 0:
			y += speed;
			break;
		case 1:
			x += speed;
			break;
		case 2:
			y -= speed;
			break;
		case 3:
			x -= speed;
			break;
		default:
			break;
		}
	}

}