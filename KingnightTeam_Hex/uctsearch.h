#ifndef UCTSEARCH_H
#define UCTSEARCH_H
#include"hexdefine.h"
#include <iostream>
#include<vector>
#include<ctime>
#include <stdio.h>
#include"findachannel.h"
#include"uctnode.h"
#include"computer.h"
#include"dfs.h"
#include"playchess_start.h"
#include"location.h"
#include"commonmethod.h"
#include"judgeiswin.h"
/*
 *
 * 用于后期的搜索
*/
class UctSearch
{
public:
    UctSearch();
    UctSearch(int bo[ROW][COLUMN]);
	PlayChess_Start ps;
	CommonMethod cm;
	JudgeIsWin jiw;
    int board[ROW][COLUMN];
    int UCTK = 1;
    int randomresult;
    int chessNum = 0;
    int drawCount = 0;
    int winCount = 0;
    int nowPlayer;
    int vnowPlayer;
    UCTMove search();
    void PlaySimulation(UCTNode *root);     //1次UCT模拟,核心过程
    int checkWin(int board[][COLUMN]);      //检查是否棋局是否结束
	int checkWinMust(int board[][COLUMN]);
    int PlayRandomGame(UCTNode *root);      //双方随机下棋直到终局,返回胜方
    void setVchess(int player,int &v_chessNum,int v_board[][COLUMN]);
    void CreateChildren(UCTNode *root);//生成符合规则的子节点
    //UCT最优节点选择.公式UCT = UCTK * sqrt(log(root->visit) / (5 * next->visit))
   //该公式与访问节点的频数与淘汰劣质节点有关(分子分母决定),性质未详细证明.
    UCTNode* UctSearch::UCTSelect(UCTNode *root);
    //下子
    void makeMove(UCTMove move);
    void unmakeMove(UCTMove move);
    void UpdateWin(UCTNode *root, int result);  //更新根节点胜率
    void SetBest(UCTNode *root);    //设置根节点最优走步
    bool isWin(int board[][COLUMN],int whoPlayer);      //判断输赢
	bool isWinMust(int board[][COLUMN], int whoPlayer);
};

#endif // UCTSEARCH_H
