#include "computer.h"

bool Computer::isImportChess = false;       //是否导入棋谱
bool Computer::isFirst = true;//电脑是否是先手
bool Computer::isStart = false;//是否开始下棋
bool Computer::isChooseFirst = false;//是否选择先手
bool Computer::isTo = false;
bool Computer::isTurn = false;      //是否轮到选手下棋
bool Computer::isSuccess = true;
int Computer::uctCount = 0;
int Computer::board[ROW][COLUMN];       //棋盘
int Computer::onTheOffensiveValue;      //先手的棋值
vector<string> Computer::record;        //下棋记录
vector<string> Computer::startBoard;    //开局库
vector<string> Computer::startBoardRecord;      //开局库中已下子的记录
vector<Location> Computer::chessFile;       // 导入的棋谱
int Computer::step = 0 ;
Computer::Computer(){
    initBoard(board);
}

//初始化棋盘
void Computer::initBoard(int board[ROW][COLUMN]){
    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            board[i][j] = NO_CHESS;
        }
    }
}
