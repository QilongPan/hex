#ifndef FINDTHELONGESTSTEPCONNECTION_H
#define FINDTHELONGESTSTEPCONNECTION_H
#include"hexdefine.h"
#include"findachannel.h"
#include"computer.h"
#include"solveHasPath.h"
#include"dfs.h"

class FindTheLongestStepConnection
{
public:
    FindTheLongestStepConnection();
    int getMaxLength_TopToBottom( int board[][COLUMN],int whoPlayer);//寻找最长连接步（从上到下）
    int startPath( int board[][COLUMN],int startX ,int startY,int endX,int endY,int whoPlayer);//判断某点到某点是否连通
    void getRecursiveArray(int** array,int whoPlayer,int board[][COLUMN]);     //得到递归的数组,返回一个0,1数组，当没有棋或是其他方的棋，设置为-1
    int getMaxLength_LeftToRight( int board[][COLUMN],int whoPlayer);//判断棋盘中能走的最多的连接步(从左到右）
};

#endif // FINDTHELONGESTSTEPCONNECTION_H
