#ifndef FINDACHANNEL_H
#define FINDACHANNEL_H
#include"hexdefine.h"


class FindAChannel
{
public:
    FindAChannel();
    FindAChannel(int** board);
    bool isConnected(int startX , int startY,int endX,int endY);//判断两个点之间是否连接
    void recursionGetPath(int startX , int startY,int endX,int endY);//得到两点连通的路径数量
    bool isCorrectIndex(int x, int y);//判断坐标是否越界
private:
    int **board;     //棋盘
    int count;      //路径数
};

#endif // FINDACHANNEL_H
