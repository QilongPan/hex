#ifndef COMMONMETHOD_H
#define COMMONMETHOD_H
#include<hexdefine.h>
#include<location.h>
#include<vector>
/*
公共方法类，包含的方法供其他类使用
*/
using namespace std;
class CommonMethod
{
public:
    CommonMethod();
    bool isValid(int x, int y);     //判断坐标是否在棋盘上越界
    bool judgeIndexIsValid(int x, int y);//判断坐标是否合法
	vector<Location> getEmptyLocationOnBoard(int board[][COLUMN]);
	bool solveHasPath(int board[][COLUMN], int startX, int startY, int endX, int endY);
	bool hasPath(int board[][COLUMN], int startX, int startY, int endX, int endY);	//判断两个点是否连通
	bool hasNextMove(const int board[][COLUMN], int x, int y,int whoPlayer);
	bool hasUpMove(const int board[][COLUMN], int x, int y, int whoPlayer);
	vector<Location> getEmptyLocationOnBoard(const int board[][COLUMN]);
	void copyTwoArray(int newBoard[][COLUMN], const int board[][COLUMN]);
	int getOtherPlayer(int whoPlayer);
};

#endif // COMMONMETHOD_H
