#include"wall.h"
#include"tankbase.h"
#include <fstream>

int W[11] = { 8 , 8 , 16 , 8 , 8 , 8 , 8 , 16 , 16 , 16 , 32 };
int H[11] = { 8 , 8 , 8 , 8 , 16 , 8 , 16 , 8 , 16 , 16 , 28 };
//int xy[500][500] = { 0 };
using namespace std;
wall::wall() {
	sx = 137;
	sy = 171;
	wallImg = new IMAGE();
	loadimage(wallImg, L"tk.png");

	life = new bool[3000];
	for (int i = 0; i < 3000; ++i) {
		life[i] = true;
	}
}
bool wall::showWall(int w[11], int h[11]) {
	ifstream in("map.txt");//读入地图文件作为输入
	int x, y, n;
	int i = 0;
	while (in >> x && in >> y && in >> n) {//循环画出地图
		if (life[i]) {
			switch (n) {
			case 0:
				sx = 137;
				sy = 171;
				break;
			case 1:
				sx = 179;
				sy = 171;
				break;
			case 2:
				sx = 205;
				sy = 171;
				break;
			case 3:
				sx = 239;
				sy = 179;
				break;
			case 4:
				sx = 273;
				sy = 171;
				break;
			case 5:
				sx = 383;
				sy = 179;
				break;
			case 6:
				sx = 451;
				sy = 171;
				break;
			case 7:
				sx = 511;
				sy = 179;
				break;
			case 8:
				sx = 613;
				sy = 171;
				break;
			case 9:
				sx = 1;
				sy = 205;
				break;
			case 10:
				sx = 647;
				sy = 173;
				break;
			}
			putimage(x, y, w[n], h[n], wallImg, sx, sy);
		}
		i++;
	}
	return true;
}
void wall::caseHit(BB *b) {

	ifstream in("map.txt");//读入地图文件作为输入
	int x, y, n;
	int i = 0;
	bool flag = false;
	while (in >> x && in >> y && in >> n) {//子弹循环检测碰撞

		if (life[i]) {
			for (int j = 0; j < b->GetNum(); ++j) {
				if (b->getLife(j)) {
					switch (b->GetDir(j)) {
					case 0:
						if (b->GetX(j) + 3 > x && b->GetX(j) + 3 <= x + W[n] && b->GetY(j) > y - 8 && b->GetY(j) < y + H[n] + 8) {
							life[i] = (n == 9) ? true : false;
							b->setLifeFalse(j);
							flag = true;
						}
						break;
					case 1:
						if (b->GetX(j) > x - 8 && b->GetX(j) < x + W[n] + 8 && b->GetY(j) + 3 > y && b->GetY(j) + 3 <= y + H[n]) {
							life[i] = (n == 9) ? true : false;
							b->setLifeFalse(j);
							flag = true;
						}
						break;
					case 2:
						if (b->GetX(j) + 3 > x  && b->GetX(j) + 3 <= x + W[n] && b->GetY(j) > y - 8 && b->GetY(j) < y + H[n] + 8) {
							life[i] = (n == 9) ? true : false;
							b->setLifeFalse(j);
							flag = true;
						}
						break;
					case 3:
						if (b->GetX(j) > x - 8 && b->GetX(j) < x + W[n] + 8 && b->GetY(j) + 3 > y && b->GetY(j) + 3 <= y + H[n]) {
							life[i] = (n == 9) ? true : false;
							b->setLifeFalse(j);
							flag = true;
						}
						break;
					}
				}

				if (flag) {
					flag = false;
					break;
				}

			}
		}
		++i;
	}


}