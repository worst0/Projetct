/*************************************************************************
	> File Name: ball_status.c
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月25日 星期四 19时52分55秒
 ************************************************************************/

#include "head.h"
#include "game.h"
extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_access(struct Point *loc) {
	int px = loc->x;
	int py = loc->y;
	if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		return 1;
	}
	return 0;
}

int can_kick(struct Point *loc, int strength){
    //palyer和ball坐标对齐
    //判断palyer和ball的坐标在上下左右2个单位距离内，则可踢球
    //根据player和ball的相对位置，计算球的运动方向，加速度方向，假设球只能在palyer和ball的延长线上运动
    //可踢返回1，否则返回0

    	int px = loc->x;
	int py = loc->y;

	if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		if (px == (int)ball.x && py == (int)ball.y) return 0;
		double tx = ball.x - px;
		double ty = ball.y - py;
		double dx = tx / sqrt(pow(tx, 2) + pow(ty, 2));
		double dy = ty / sqrt(pow(tx, 2) + pow(ty, 2));
		ball_status.a.x = -3.0 * dx;
		ball_status.a.y = -3.0 * dy;
		ball_status.v.x = 40 * strength * 0.2 * dx;
		ball_status.v.y = 40 * strength * 0.2 * dy;
		char tmp[512] = {0};
		sprintf(tmp, "a(%lf, %lf) v(%lf, %lf)", ball_status.a.x, ball_status.a.y, ball_status.v.x, ball_status.v.y);
		//Show_Message( , NULL, tmp, 1);
		return 1;
	}
	return 0;
}

