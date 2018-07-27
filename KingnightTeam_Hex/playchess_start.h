#ifndef PLAYCHESS_START_H
#define PLAYCHESS_START_H
#include<vector>
#include<string>
#include<iostream>
#include"transform.h"
#include"computer.h"
#include <time.h>
#include"negativemaxminsearch.h"
#include"commonmethod.h"
#include"alphabetasearch.h"
#include"finalalgorithm.h"
#include"location.h"

class PlayChess_Start
{
public:
    PlayChess_Start();
    Transform tf;
    CommonMethod cm;
    FinalAlgorithm fa;
	JudgeIsWin jiw;
    vector<vector<string>> startVector;      //开局库
    void initStartVector(); //初始化开局库
    string playChess();     //下棋
    string playChess_IsFirst();     //是先手
    string playChess_IsNotFirst();//是后手
    string getWhichIsWalled();      //得到自己的棋哪颗被堵
    string getWhichIsWalled_LeftToRight();
    string playChessStartSuccess();//开局库生成成功下棋
    string playChessStartSuccess_LeftToRight();
	string playChessExperience();
	std::string playChessWhenExistMustWillWin(int whoPlayer);		//当存在必赢局面时下棋
	vector<Location> getLocations(int depth, int count);
	std::vector<Location> getLocationsByIndex(int depth,int count,int x, int y,const int board[][COLUMN]);
	void getLocationsByRecursion(vector<Location> &locations, int computerX, int computerY, int depth);
	void getLocationsByRecursionByBoard(vector<Location> &locations, int computerX, int computerY, int depth,int count, const int board[][COLUMN]);
	string isExistTruncationIndex(const int board[][COLUMN],int whoPlayer);
	string playChess_TopToBottom(string lastStr);//（已过时，不再运用）
	string playChess_LeftToRight(string lastStr);//（已过时，不再运用）
	

};

#endif // PLAYCHESS_START_H
