#pragma once
#include<graphics.h>
#include"bb.h"
#include"tankbase.h"
/******************************墙类*********************************/
class wall {
private:

	int sx, sy;
	IMAGE* wallImg;									//存储墙图


public:
	bool* life;										//判断wall是否存在
	wall();											//初始化
	bool showWall(int w[11], int h[11]);				//读取地图数据文件并画出地图
	void caseHit(BB *b);							//检测是否被子弹打击



};
/*******************************************************************/