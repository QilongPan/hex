#ifndef COMPUTER_H
#define COMPUTER_H
#include"hexdefine.h"
#include"location.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class Computer
{
public:
    Computer();
    static bool isImportChess;  //是否导入棋谱
    static int step;     //跳到指定步数
    static bool isFirst;        //是否是先手
    static bool isStart;        //游戏是否开始
    static bool isChooseFirst;  //是否选择先手
    static bool isSuccess;  //开局库是否成功
    static bool isTurn; //是否轮到选手下棋
    static bool isTo;
    static int board[ROW][COLUMN];  //棋盘
    static int onTheOffensiveValue; //先手棋子
    static vector<string> record;       //下棋棋子记录
    void initBoard(int board[ROW][COLUMN]);       //初始化棋盘
    static vector<string> startBoard;       //开局库
    static vector<string> startBoardRecord;     //开局库中已下子的记录
    static vector<Location> chessFile;        //棋谱中所获得的棋子
	static int uctCount;
};

#endif // COMPUTER_H
