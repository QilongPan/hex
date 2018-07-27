#ifndef FINALALGORITHM_H
#define FINALALGORITHM_H
#include<string>
#include<iostream>
#include"computer.h"
#include<vector>
#include"location.h"
#include"move.h"
#include"judgeiswin.h"
#include"transform.h"
#include"solveHasPath.h"
#include"commonmethod.h"

/*
 * 终局算法
*/
class FinalAlgorithm
{
public:
    FinalAlgorithm();
    JudgeIsWin jiw = JudgeIsWin();
    Transform tf = Transform();
	CommonMethod cm;
    string isExistMustWin(int board[][COLUMN],int whoPlayer,int n);   //是否存在必赢路径
	string isExistWillMustWin(int whoPlayer);		//是否存在将要必赢的走步
	vector<Location> getExistWillMustWinChessComb(int board[][COLUMN], int whoPlayer);
    vector<Location> getEmptyChessOnBoard(const int board[][COLUMN]);      
    void makeMove(Move move ,int board[][COLUMN]);
	void makeMoves(vector<Location>, int board[][COLUMN],int whoPlayer);
	void unMakeMoves(vector<Location>, int board[][COLUMN]);
    void unMakeMove(Move move,int board[][COLUMN]);
	vector<Location> updateLocationsScore(vector<vector<Location>> locationsVec,int whoPlayer,vector<Location>& locations);
	int getMaxLengthAddChess(int board[][COLUMN], int whoPlayer);
	int getMaxLength(int board[][COLUMN],int whoPlayer);		//得到棋盘的最长连接步
	int getMaxLength_Actual(int board[][COLUMN], int whoPlayer);
	int getMaxLengthTopToBottom(int board[][COLUMN], int whoPlayer);
	int getMaxLengthTopToBottom_Actual(int board[][COLUMN], int whoPlayer);
	int getMaxLengthLeftToRight(int board[][COLUMN], int whoPlayer);
	int getMaxLengthLeftToRight_Actual(int board[][COLUMN], int whoPlayer);
	Location getBestLocation(vector<Location> locations, int whoPlayer);	//得到最好的下棋位置
	void  computeAllChoices(std::vector<Location> &data, int n, vector<vector<Location>>& locationsVec, int startIndex, int m,
		vector<Location>& arr, int arrIndex);
	vector<vector<Location>> getCombsByEmptyChess(vector<vector<Location>>& locationsVec, vector<Location> locations, int number);//(已过时）
};

#endif // FINALALGORITHM_H
