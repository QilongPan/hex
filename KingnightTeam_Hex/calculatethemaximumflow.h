#ifndef CALCULATETHEMAXIMUMFLOW_H
#define CALCULATETHEMAXIMUMFLOW_H
#include<iostream>
#include<vector>
#include"hexdefine.h"
#include"computer.h"
#include"commonmethod.h"
#include<queue>
#include<stdio.h>
using namespace std;
class CalculateTheMaximumFlow
{
public:
    CalculateTheMaximumFlow();
	CommonMethod cm;
    void Ford_Fulkerson(int **c, int vertexNum, int s, int t, int **f);
    void calculateENet(int **c, int vertexNum, int **f, int **e);
    int findRoute(int **e, int vertexNum, int *priorMatrix, int s,int t);
    int getFord(int board[][COLUMN],int whoPlayer);
	//棋盘转换为缩略图（从上到下)
    void boardChangeToThumbnail( const int board[][COLUMN],int whoPlayer,int thumbnail[][INITMAPNUMBER] );
	//棋盘转换为缩略图(从左到右)
	void boardChangeToThumbnail_LeftToRight(const int board[][COLUMN], int whoPlayer, int thumbnail[][INITMAPNUMBER]);
    std::vector<int> getPointToPointVector(const int thumbnail[][123],int point);     //得到指向该节点的点
    //得到一个节点到另一个节点的流量
    int getNodeFlow(int start , int end);
    //判断两个节点是否相邻
    bool judgeIsAdjacent(int startNodeRow,int startNodeColumn, int endNodeRow,int endNodeColumn);
	bool hasPath(int rGraph[][INITMAPNUMBER], int s, int t, int path[]);
	int maxFlow(int graph[][INITMAPNUMBER], int s, int t);
};

#endif // CALCULATETHEMAXIMUMFLOW_H
