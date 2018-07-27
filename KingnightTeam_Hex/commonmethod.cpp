#include "commonmethod.h"
#include "computer.h"
CommonMethod::CommonMethod()
{

}
//判断坐标是否在棋盘上越界
bool CommonMethod::isValid(int x, int y){
    if(x >= ROW
            || x < 0
            || y >= COLUMN
            || y < 0){
        return false;
    }
    return true;
}

//判断下棋位置是否合法
bool CommonMethod::judgeIndexIsValid(int x, int y){
  if(isValid(x,y)){
      return Computer::board[x][y] == NO_CHESS?true:false;
  }
      return false;
}
vector<Location> CommonMethod::getEmptyLocationOnBoard(int board[][COLUMN])
{
	vector<Location> emptyLocations;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			if (board[i][j] == NO_CHESS)
			{
				emptyLocations.push_back(Location(i, j));
			}
		}
	}
	return emptyLocations;
}

bool CommonMethod::hasPath(int board[][COLUMN], int startX, int startY, int endX, int endY){
	/*if (moves.size() == 0) { return  false; }
	Location &current_move = moves.top();
	// 当找到x = 10的点
	if (current_move.getX() == (ROW - 1)) { return true; }
	int x = current_move.getX(),
		y = current_move.getY();
	moves.pop();
	add_neighbor(x - 1, y);
	add_neighbor(x - 1, y + 1);
	add_neighbor(x, y - 1);
	add_neighbor(x, y + 1);
	add_neighbor(x + 1, y - 1);
	add_neighbor(x + 1, y);
	return dfs_find();*/
	return true;
}
/*
	作用：用于判断棋盘中某一位置在上下两行相邻位置是否全是敌方棋子
	参数：board棋盘，x横坐标，y纵坐标
*/
bool CommonMethod::hasNextMove(const int board[][COLUMN], int x, int y,int whoPlayer)
{
	if (whoPlayer == Computer::onTheOffensiveValue)
	{
		if (x == ROW - 1)
		{
			return true;
		}
		else{
			if (isValid(x + 1, y) && board[x + 1][y] == NO_CHESS)
			{
				return true;
			}
			if (isValid(x + 1, y - 1) && board[x + 1][y - 1] == NO_CHESS)
			{
				return true;
			}
			return false;
		}
		
	}
	else{
		if (y == COLUMN - 1)
		{
			return true;
		}
		else{
			if (isValid(x - 1, y + 1) && board[x - 1][y + 1] == NO_CHESS)
			{
				return true;
			}
			if (isValid(x , y + 1) && board[x][y + 1] == NO_CHESS)
			{
				return true;
			}
			return false;
		}
	}
	
}

bool CommonMethod::hasUpMove(const int board[][COLUMN], int x, int y, int whoPlayer)
{
	if (whoPlayer == Computer::onTheOffensiveValue)
	{
		if (x == 0)
		{
			return true;
		}
		else{
			if (isValid(x - 1, y) && board[x - 1][y] == NO_CHESS)
			{
				return true;
			}
			if (isValid(x - 1, y + 1) && board[x - 1][y + 1] == NO_CHESS)
			{
				return true;
			}
			return false;
		}

	}
	else{
		if (y == 0)
		{
			return true;
		}
		else{
			if (isValid(x , y - 1) && board[x][y - 1] == NO_CHESS)
			{
				return true;
			}
			if (isValid(x+1, y - 1) && board[x+1][y - 1] == NO_CHESS)
			{
				return true;
			}
			return false;
		}
	}
}

//得到棋盘上空点
vector<Location> CommonMethod::getEmptyLocationOnBoard(const int board[][COLUMN])
{
	std::vector<Location> locations;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			if (board[i][j] == NO_CHESS)
			{
				locations.push_back(Location(i, j));
			}
		}
	}
	return locations;
}

//复制二维数组
void CommonMethod::copyTwoArray(int newBoard[][COLUMN], const int board[][COLUMN])
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			newBoard[i][j] = board[i][j];
		}
	}
}

int CommonMethod::getOtherPlayer(int whoPlayer)
{
	if (whoPlayer == COMPUTER_CHESS)
	{
		return PLAYER_CHESS;
	}
	else{
		return COMPUTER_CHESS;
	}
}