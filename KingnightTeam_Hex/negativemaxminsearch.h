#ifndef NEGATIVEMAXMINSEARCH_H
#define NEGATIVEMAXMINSEARCH_H
#include"move.h"
#include"hexdefine.h"
#include<vector>
#include<iostream>
#include"judgeiswin.h"
#include"findthelongeststepconnection.h"
#include"calculatethemaximumflow.h"
#include"playchess_start.h"
using namespace  std;


class NegativeMaxMinSearch
{
public:
    NegativeMaxMinSearch();
    NegativeMaxMinSearch(int board[][COLUMN]);
    void search();
    Move bestMove;
    JudgeIsWin jiw = JudgeIsWin();          //判断是否赢得类
    FindTheLongestStepConnection ftlsc = FindTheLongestStepConnection();//寻找最长连接步
	CalculateTheMaximumFlow ctm = CalculateTheMaximumFlow();
//	PlayChess_Start ps = PlayChess_Start();
    int search_NegativeMinimaxValue(int depth,Move move,int board[][COLUMN]);//负极大极小值搜索
    bool isComputerOnLastDepth(int depth);//判断搜索的最后一层是不是电脑
    vector<Move> getAllMove(int moveDirection,int board[][COLUMN]);
    void makeMove(Move move ,int board[][COLUMN]);      //产生局面
    void unMakeMove(Move move,int board[][COLUMN]);       //恢复局面
    int evaluation(int board[][COLUMN],int whoPlayer);      //评估函数
    int getOtherPlayer(int whoPlayer);//得到另一家选手
    Move getMove();
private:
    int pieces[ROW][COLUMN];       //棋盘

};

#endif // NEGATIVEMAXMINSEARCH_H
