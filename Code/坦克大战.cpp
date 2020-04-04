#include<iostream>
#include<conio.h>
#include<graphics.h>
#include"tankbase.h"
#include"wall.h"
#include <fstream>
#include<thread>
#include<ctime>
#include<cstdlib>
#include"bb.h"
#include <dsound.h>
#include<Windows.h>
#include <Digitalv.h>
#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库 
#define NUM 5


void begin() {
	while (1) {
		if (GetKeyState(79) & 0x8000) {
			system("start BeginPicture.exe");
			closegraph();
			exit(1);
		}
	}
}

using namespace std;
int* music = new int(2);

void delay(DWORD ms);
int caseIsPass(tank* Tank, wall* Wall, tank*Tank2);	//检测是否有坦克想通过
int caseIsPassai(tank* Tank, tank* Tank2);
void PlayMp3();
int judgeOver(wall* Wall, tank* Tank);
void MUSIC();

int w[11] = { 8 , 8 , 16 , 8 , 8 , 8 , 8 , 16 , 16 , 16 , 32 };
int h[11] = { 8 , 8 , 8 , 8 , 16 , 8 , 16 , 8 , 16 , 16 , 28 };
//int testd[NUM] = { 0 };
int CountT = 0;





int main(char* args) {
	thread begin(begin);
	begin.detach();
	PlayMp3();
	thread m1(MUSIC);
	srand((unsigned)time(NULL));

	initgraph(470, 480);				//初始化500*500画布
	m1.detach();
begin:

	IMAGE maingui;
	loadimage(&maingui, L"main.png", 470, 480);
	putimage(0, 0, &maingui);
	while (!GetAsyncKeyState(13) & 0x8000);

	IMAGE graph1(470, 480);
	SetWorkingImage(&graph1);

	BB b;								//初始化子弹

	wall Wall;							//初始化墙
	tank Tank;							//初始化坦克
	AI ai[NUM];
	Tank.setSpeed(4);					//设置坦克速度

	for (int i = 0; i < NUM; ++i) {
		ai[i].setSpeed(4);
	}
	ai[0].setXY(0, 0);
	ai[3].setXY(70, 0);
	ai[1].setXY(150, 0);
	ai[4].setXY(220, 0);
	ai[2].setXY(290, 0);

	int sum = 0;

	long start = clock();
	while (1) {

		Wall.caseHit(&b);
		CountT++;
		SetWorkingImage(&graph1);
		setbkcolor(BLACK);				//设置画布背景色为黑色
		cleardevice();					//用当前背景色刷新画布
		b.bbShow();
		Wall.showWall(w, h);				//显示map
		Tank.show();//显示坦克和ai
		if (AI::beataisum == 2 * NUM) {//判断胜利条件
			int Prize;
			if ((clock() - start) * 0.08 < 8000) {
				Prize = 10000 - 500 * Tank.Getloss() - (clock() - start) * 0.08;
			}
			else {
				Prize = 2000 - 500 * Tank.Getloss();
			}

			IMAGE img;
			loadimage(&img, L"tkOver.png", 470, 480);
			SetWorkingImage();
			putimage(0, 0, &img);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("宋体"));
			outtextxy(150, 300, L"YOU WIN");
			outtextxy(100, 340, L"SCORE:");
			int i = 0;
			while (Prize) {


				switch (Prize % 10) {
				case 0:
					outtextxy(340 - i * 20, 340, L'0');
					break;
				case 1:
					outtextxy(340 - i * 20, 340, L'1');
					break;
				case 2:
					outtextxy(340 - i * 20, 340, L'2');
					break;
				case 3:
					outtextxy(340 - i * 20, 340, L'3');
					break;
				case 4:
					outtextxy(340 - i * 20, 340, L'4');
					break;
				case 5:
					outtextxy(340 - i * 20, 340, L'5');
					break;
				case 6:
					outtextxy(340 - i * 20, 340, L'6');
					break;
				case 7:
					outtextxy(340 - i * 20, 340, L'7');
					break;
				case 8:
					outtextxy(340 - i * 20, 340, L'8');
					break;
				case 9:
					outtextxy(340 - i * 20, 340, L'9');
					break;
				}
				Prize /= 10;
				i++;


			}

			AI::beataisum = 0;
			goto end;
		}

		for (int i = 0; i < NUM; ++i) {
			ai[i].show();
			if (ai[i].getLife() == false) {
				sum++;
			}
		}
		if (sum == NUM) {
			for (int i = 0; i < NUM; ++i) {
				//if (!ai[i].getLife()) {
				ai[i].setLife(true);
				ai[i].setXY((450 / NUM)*i, 0);
				//}

			}
			sum = 0;
			AI::beataisum += NUM;
		}
		else {
			sum = 0;
		}
		int test;
		test = Tank.move(&b, CountT, 1, music);

		for (int i = 0; i < NUM; ++i) {
			/*	if (testd[i] == 0) {
					testd[i] = 15 + rand() % 20;
					ai[i].move(&b, CountT, 1, rand() % 4);
					continue;
				}
				if (ai[i].getLife() && testd[i]--) {
					ai[i].move(&b, CountT, 1);
				}
			*/
			if (ai[i].getLife())
				ai[i].move(&b, CountT, 1);
		}

		if (judgeOver(&Wall, &Tank)) {
			AI::beataisum = 0;
			if (_kbhit())
			{
				while (_kbhit()) {
					_getch();
				}
			}
			//Sleep(1000);
			goto end;
		}


		Tank.caseHit(&b, 1, music);
		for (int i = 0; i < NUM; ++i) {//碰撞检测,可优化

			if (ai[i].getLife())
				ai[i].caseHit(&b, 0, music);
			if (caseIsPass(&Tank, &Wall, ai + i)) {
				if (ai[i].getLife() && !test && caseIsPassai(&Tank, ai + i)) {
					ai[i].move(&b, CountT, 0, rand() % 4);
				}
				else {// if(caseIsPass(&Tank, &Wall, ai + i) == 2) {
					Tank.move(&b, CountT, 0, music);
				}

			}
			if (ai[i].getLife() && caseIsPass(ai + i, &Wall, &Tank)) {
				/*if (!test && caseIsPass(&ai, &Wall, &Tank) == 1) {
					Tank.move(&b, CountT, 0);
				}
				else {
					ai.move(&b, CountT, 0);
				}*/
				ai[i].move(&b, CountT, 0, rand() % 4);
				if (ai[i].id == 0) {
					if (ai[i].getDir() == 2 || ai[i].getDir() == 0) {
						ai[i].setDir((rand() % 2) ? 1 : 3);
					}
					else if (ai[i].getDir() == 3 || ai[i].getDir() == 1) {
						ai[i].setDir((rand() % 4 == 0) ? 0 : 2);
					}
					//ai[i].setDir((ai[i].getDir() + (rand()%2)) % 4);

				}

			}
			for (int j = 0; j < NUM; ++j)
				if (ai[i].getLife() && ai[j].getLife() && i != j && caseIsPassai(ai + i, ai + j)) {
					/*if (!test && caseIsPass(&ai, &Wall, &Tank) == 1) {
						Tank.move(&b, CountT, 0);
					}
					else {
						ai.move(&b, CountT, 0);
					}*/
					//ai[i].move(&b, CountT, 0, rand() % 4);
					/*if (ai[i].getDir() == 2 || ai[i].getDir() == 0) {
						ai[i].setDir((rand() % 2) ? 1 : 3);

					}
					else if (ai[i].getDir() == 3 || ai[i].getDir() == 1) {
						ai[i].setDir(2);
					}

					if (ai[j].getDir() == 2 || ai[j].getDir() == 0) {
						ai[j].setDir((rand() % 2) ? 1 : 3);

					}
					else if (ai[j].getDir() == 3 || ai[j].getDir() == 1) {
						ai[j].setDir(2);
					}
					*/

					ai[i].setDir((ai[i].getDir() + 2) % 4);//success

				}
		}


		//Sleep(40);
		SetWorkingImage();
		putimage(0, 0, &graph1);
		delay(30);

	}
	_getch();
end:
	while (1) {
		if (_kbhit()) {
			if (_getch() == 13) {
				break;
			}
		}
	}
	//Sleep(3000);
	goto begin;

	return 0;
}







int caseIsPass(tank* Tank, wall* Wall, tank* Tank2) {
	ifstream in("map.txt");							//读入地图文件作为输入
	int x, y, n;
	int i = 0;

	if (Tank->getX() < 0 || Tank->getX() > 444 || Tank->getY() < 0 || Tank->getY() > 454)//越界检测
	{

		return 2;
	}


	if (Tank->id == Tank2->id&&Tank->getLife() && Tank2->getLife() && abs(Tank->getX() - Tank2->getX()) < 40 && abs(Tank->getY() - Tank2->getY()) < 40) {

		return 1;
	}
	if (Tank->getLife() && Tank2->getLife() && abs(Tank->getX() - Tank2->getX()) < 26 && abs(Tank->getY() - Tank2->getY()) < 26) {
		return 1;
	}
	while (in >> x && in >> y && in >> n) {												//循环检测碰撞
		if (Wall->life[i]) {
			if (x - 26 < Tank->getX() && x + w[n] > Tank->getX() && y + h[n] > Tank->getY() && y - 26 < Tank->getY()) {

				return 2;
			}
		}
		++i;
	}
	return 0;
}

int caseIsPassai(tank* Tank, tank* Tank2) {

	if (abs(Tank->getX() - Tank2->getX()) < 26 && abs(Tank->getY() - Tank2->getY()) < 26) {

		return 1;
	}

	return 0;
}

void delay(DWORD ms) {// 绝对延时
	DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}
void PlayMp3() {
	char buf[128];
	char str[128] = { 0 };
	int i = 0;

	//use mciSendCommand
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	//SetWindowText(NULL,"12345");
	mciOpen.lpstrDeviceType = TEXT("mpegvideo");
	mciOpen.lpstrElementName = TEXT("bk.wav");
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)& mciOpen);//MCI_DGV_PLAY_REPEAT 循环
	if (mciError) {
		mciGetErrorString(mciError, (LPWSTR)buf, 128);
		printf("send MCI_OPEN command failed:%s\n", buf);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;

	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD_PTR)& mciPlay);
	if (mciError) {
		printf("send MCI_PLAY command failed\n");
		return;
	}
}

void MUSIC() {


	//PlaySoundW(TEXT("bkmusic.wav"), NULL, SND_LOOP| SND_SYNC);	//播放wav音乐,循环播放
	while (1) {
		//if (*music == 0) {
		//	PlaySoundW(L"player.move.wav", NULL, SND_FILENAME | SND_SYNC);
		//}
		if (*music == 1) {
			Beep(523, 100);
			//PlaySoundW(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_SYNC);
		}
		if (*music == 3) {
			PlaySoundW(TEXT("kill.wav"), NULL, SND_FILENAME | SND_SYNC);
		}

	}


}
int judgeOver(wall* Wall, tank* Tank) {
	IMAGE img;
	loadimage(&img, L"tkOver.png", 470, 480);
	if (Tank->Getloss() == 4) {
		SetWorkingImage();
		putimage(0, 0, &img);
		Tank->Setloss(0);
		return 1;
	}
	if ((Wall->life)[281] == 0) {
		SetWorkingImage();
		putimage(0, 0, &img);
		Tank->Setloss(0);
		return 1;
	}
	return 0;
}
