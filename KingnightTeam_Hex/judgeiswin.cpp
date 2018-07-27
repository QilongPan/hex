#include "judgeiswin.h"

JudgeIsWin::JudgeIsWin()
{

}

/*
选手whoPlayer在棋盘board中是否已经连通（即赢棋）
*/
bool JudgeIsWin::isWin(const int board[][COLUMN], int whoPlayer)
{   //先手
    if (whoPlayer == Computer::onTheOffensiveValue)
	{	
        Board<int> tempBoard(board);
        redDFS searcher(&tempBoard, whoPlayer);
        return searcher.solve();
    }
    else //后手
	{
        Board<int> tempBoard(board);
        blueDFS searcher(&tempBoard,whoPlayer );
        return searcher.solve();	
    }
}

/*
选手whoPlayer在棋盘board中是否已经达到必赢局面
*/
bool JudgeIsWin::isWillMustWin(const int board[][COLUMN], int whoPlayer)
{
		Board<int> tempBoard(board);
		isHasPathWillMustWin hpwm(&tempBoard, whoPlayer);
		return hpwm.solve();
}

