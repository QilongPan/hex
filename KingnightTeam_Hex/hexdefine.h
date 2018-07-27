#ifndef HEXDEFINE_H
#define HEXDEFINE_H
#define ROW 11  //棋盘的行
#define COLUMN 11   //棋盘的列
#define PASS 1  //通过，棋盘中的位置是该为选手的棋
#define NO_PASS -1  //不通过
#define ALREADY_PASS 5;	//已经通过的点
#define NO_CHESS 0      //没有棋
#define COMPUTER_CHESS 1 //电脑的棋
#define PLAYER_CHESS 2	//选手的棋
#define SEARCH_DEPTH 1 //搜索深度
#define COMPUTER_WIN 2  //电脑赢
#define PLAYER_WIN 1 //选手赢
#define DRAW 5//没有输赢
#define NORESULT 0  //没有结果
#define ALLCHESSNUMBER 121//棋子数目
#define MAXVALUE 20000 //评估最大值
#define UCTSTARTTIME 30 //uct启动棋子数目
#define INITMAPNUMBER 123 //计算最大流的节点数
#define FINDDEPTH 2 //查找最好坐标出现的层数 //原来为2
#define FINDNUMBER 70	//查找坐标数
#define K 3//从n个选k个
#define ISCUTOFF 1
#define ALPHABETASEARCHDEPTH 3
#endif // HEXDEFINE_H
