#ifndef JUDGEISWIN_H
#define JUDGEISWIN_H
#include"hexdefine.h"
#include"computer.h"
#include"findachannel.h"
#include"dfs.h"
#include"isHasPathWillMustWin.h"
class JudgeIsWin
{
public:
    JudgeIsWin();
    bool isWin(const int board[][COLUMN],int whoPlayer);      //判断输赢
	bool isWillMustWin(const int board[][COLUMN], int whoPlayer);	//该局面将来是否一定会赢
};

#endif // JUDGEISWIN_H
