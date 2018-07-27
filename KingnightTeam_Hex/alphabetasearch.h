#ifndef ALPHABETASEARCH_H
#define ALPHABETASEARCH_H
#include"hexdefine.h"
#include"judgeiswin.h"
#include"move.h"
#include"location.h"
#include"findthelongeststepconnection.h"
#include"calculatethemaximumflow.h"
#include"finalalgorithm.h"
class AlphaBetaSearch
{
public:
    JudgeIsWin jiw = JudgeIsWin();      //判断是否赢棋
    AlphaBetaSearch();
	FinalAlgorithm fa;
    Move move;
    FindTheLongestStepConnection ftlsc = FindTheLongestStepConnection();//寻找最长连接步
    CalculateTheMaximumFlow ctm = CalculateTheMaximumFlow();

    int board[ROW][COLUMN];
    AlphaBetaSearch(int pieces[][COLUMN]);
    int search_AlphaBeta(int depth,int nAlpha,int nBeta);
    vector<Move> AlphaBetaSearch::getAllMove(int board[][COLUMN]);
    void makeMove(Move move ,int board[][COLUMN],int whoPlayer);
    void unMakeMove(Move move,int board[][COLUMN]);       //恢复局面
    int evaluation(int board[][COLUMN],int whoPlayer);      //评估函数
    bool isComputerOnLastDepth(int depth);//判断搜索的最后一层是不是电脑
    int getOtherPlayer(int whoPlayer);//得到另一家选手
	bool isWin(int board[][COLUMN]);	
	bool isWillWin(int board[][COLUMN]);
	int getPlayer(int depth);
};

#endif // ALPHABETASEARCH_H
