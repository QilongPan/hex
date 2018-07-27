#include "finalalgorithm.h"

FinalAlgorithm::FinalAlgorithm()
{

}

/*
玩家whoplayer是否在board棋盘空处增加N颗己方棋子存在必赢局面
*/
string FinalAlgorithm::isExistMustWin(int board[][COLUMN],int whoPlayer,int n)
{
	vector<Location> vl = getEmptyChessOnBoard(board);
    for(int i = 0 ; i < vl.size() ; i++)
	{
        Move move = Move(vl.at(i),whoPlayer);
        makeMove(move,Computer::board);
        if(jiw.isWin(Computer::board,whoPlayer))
		{
            unMakeMove(move,Computer::board);
            return tf.getInputString(move.getLocation().getX(),move.getLocation().getY());
        }
        else
		{
            unMakeMove(move,Computer::board);
        }

    }
    return "";
}

string FinalAlgorithm::isExistWillMustWin(int whoPlayer){
	//如果本身就存在，则返回success
	if (jiw.isWillMustWin(Computer::board, whoPlayer)){
		return "success";
	}
	vector<Location> vl = getEmptyChessOnBoard(Computer::board);
	for (int i = 0; i < vl.size(); i++)
	{
		Move move = Move(vl.at(i), whoPlayer);
		makeMove(move, Computer::board);
		if (jiw.isWillMustWin(Computer::board, whoPlayer))
		{
			unMakeMove(move, Computer::board);
			return tf.getInputString(move.getLocation().getX(), move.getLocation().getY());
		}
		else
		{
			unMakeMove(move, Computer::board);
		}

	}
	return "";
}

/*
获得选手whoPlayer棋盘board中必赢局面需要添加的棋子集合(在存在必赢局面的时候调用)
*/
vector<Location> FinalAlgorithm::getExistWillMustWinChessComb(int board[][COLUMN], int whoPlayer)
{
	vector<Location> locations = getEmptyChessOnBoard(board);
	vector<vector<Location>> locationsVec;
	vector<Location> arr;
	for (int i = 1; i < 11; ++i)
	{
		computeAllChoices(locations, locations.size(), locationsVec, 0, i, arr, 0);
		for (int j = 0; j < locationsVec.size(); ++j)
		{
			makeMoves(locationsVec.at(j),board,whoPlayer);
			if (jiw.isWin(board, whoPlayer))
			{
				unMakeMoves(locationsVec.at(j), board);
				return locationsVec.at(j);
			}
			unMakeMoves(locationsVec.at(j), board);
		}
		locationsVec.clear();
		arr.clear();
	}
	return locations;
}

/*
得到在棋盘board中空的位置
*/
vector<Location> FinalAlgorithm::getEmptyChessOnBoard(const int board[][COLUMN])
{
    vector<Location> vl;
    for(int i = 0 ; i < ROW ; i++)
	{
        for(int j = 0 ; j < COLUMN ; j++)
		{
            if(board[i][j] == NO_CHESS)
			{
                Location location = Location(i,j);
                vl.push_back(location);
            }
        }
    }
    return vl;
}

//产生局面
void FinalAlgorithm ::makeMove(Move move ,int board[][COLUMN])
{
    if(move.getMoveDirection() == COMPUTER_CHESS)
	{
        board[move.getLocation().getX()][move.getLocation().getY()]
                =COMPUTER_CHESS;
    }
    else
	{
        board[move.getLocation().getX()][move.getLocation().getY()]
                =PLAYER_CHESS;
    }
}

void FinalAlgorithm::makeMoves(vector<Location> moves, int board[][COLUMN],int whoPlayer)
{
	for (int i = 0; i < moves.size(); i++)
	{
		Location move = moves.at(i);
		if (whoPlayer == COMPUTER_CHESS)
		{
			board[move.getX()][move.getY()]
				= COMPUTER_CHESS;
		}
		else{
			board[move.getX()][move.getY()]
				= PLAYER_CHESS;
		}
	}
}

//恢复局面
void FinalAlgorithm::unMakeMove(Move move,int board[][COLUMN])
{
    board[move.getLocation().getX()][move.getLocation().getY()]
            = NO_CHESS;
}

void FinalAlgorithm::unMakeMoves(vector<Location> moves, int board[][COLUMN])
{
	for (int i = 0; i < moves.size(); i++)
	{
		board[moves.at(i).getX()][moves.at(i).getY()] = NO_CHESS;
	}
}

//根据最长连接步更新结点分数
vector<Location> FinalAlgorithm::updateLocationsScore(vector<vector<Location>> locationsVec, int whoPlayer, vector<Location>& locations)
{
	for (int i = 0; i < locationsVec.size(); i++)
	{
		makeMoves(locationsVec.at(i), Computer::board,whoPlayer);
		int maxLength = getMaxLength(Computer::board, whoPlayer);
		for (int k = 0; k < locationsVec.at(i).size(); k++)
		{
			for (int n = 0; n < locations.size(); n++)
			{
				if (locations.at(n) == locationsVec.at(i).at(k))
				{
					locations.at(n).setScore(locations.at(n).getScore() + maxLength);
				}
			}
		}
		unMakeMoves(locationsVec.at(i), Computer::board);
	}
	return locations;
}

//得到选手的最长连接步
int FinalAlgorithm::getMaxLength( int board[][COLUMN],int whoPlayer)
{
	if (whoPlayer == Computer::onTheOffensiveValue){
		return getMaxLengthTopToBottom(board, whoPlayer);
	}
	else{
		return getMaxLengthLeftToRight(board, whoPlayer);
	}
}
//得到选手的最长连接步
int FinalAlgorithm::getMaxLength_Actual(int board[][COLUMN], int whoPlayer)
{
	if (whoPlayer == Computer::onTheOffensiveValue){
		return getMaxLengthTopToBottom_Actual(board, whoPlayer);
	}
	else{
		return getMaxLengthLeftToRight_Actual(board, whoPlayer);
	}
}

//得到先手的最长连接步
int FinalAlgorithm::getMaxLengthTopToBottom(int board[][COLUMN], int whoPlayer)
{
	for (int maxLength = 10; maxLength > 0; maxLength--)//连接步长度
	{
		for (int startX = 0; startX < ROW - maxLength; startX++)	//起始行
		{
			for (int startY = 0; startY < COLUMN; startY++)//起始列
			{
				if (board[startX][startY] == whoPlayer && cm.hasUpMove(board,startX,startY,whoPlayer))		//起始坐标
				{
					Board<int> tempBoard(board);
					isHasPathWillMustWin hpwm(&tempBoard, whoPlayer);
					if (hpwm.solveIsCanPut2(startX, startY)){		//向上通
						int endX = startX + maxLength;
						for (int endY = 0; endY < COLUMN; endY++)
						{
							if (board[endX][endY] == whoPlayer && cm.hasNextMove(board, endX, endY, whoPlayer))	//终点坐标并且得含有下一步可走空棋
							{
								Board<int> tempBoard2(board);
								isHasPathWillMustWin hpwm2(&tempBoard, whoPlayer);
								if (hpwm2.solveIsCanPut(endX, endY)){		//向下通
									Board<int> tempBoard(board);
									solveRedAndBlue srab(&tempBoard, whoPlayer, startX, startY, endX, endY);
									if (srab.solveWillArriveMaxLength())
									{
										if (cm.isValid(startX - 1, startY) && Computer::board[startX - 1][startY] == NO_CHESS
											&&cm.isValid(startX - 1, startY + 1) && Computer::board[startX - 1][startY + 1] == NO_CHESS)
										{
											maxLength += 1;
										}
										if (cm.isValid(endX + 1, endY) && Computer::board[endX + 1][endY] == NO_CHESS
											&&cm.isValid(endX + 1, endY - 1) && Computer::board[endX + 1][endY - 1] == NO_CHESS)
										{
											maxLength += 1;
										}
										return maxLength;
									}
								}
							}
						}
					}
					
					
				}
			}
		}
	}
	return 0;
}
//增加一颗棋之后的最长长度 
int FinalAlgorithm::getMaxLengthAddChess(int board[][COLUMN], int whoPlayer)
{
	vector<Location> emptyLocations = cm.getEmptyLocationOnBoard(board);
	int maxLength = 0;
	for (int i = 0; i < emptyLocations.size(); ++i)
	{
		makeMove(Move(emptyLocations.at(i), whoPlayer), board);
		int length = getMaxLength(board, whoPlayer);
		if (length > maxLength)
		{
			maxLength = length;
		}
		unMakeMove(Move(emptyLocations.at(i), whoPlayer), board);
	}
	return maxLength;
}


//得到先手实际的最长连接步
int FinalAlgorithm::getMaxLengthTopToBottom_Actual(int board[][COLUMN], int whoPlayer)
{
	for (int maxLength = 10; maxLength > 0; maxLength--)//连接步长度
	{
		for (int startX = 0; startX < ROW - maxLength; startX++)	//起始行
		{
			for (int startY = 0; startY < COLUMN; startY++)//起始列
			{
				if (board[startX][startY] == whoPlayer && cm.hasUpMove(board,startX,startY,whoPlayer))		//起始坐标
				{
					int endX = startX + maxLength;
					for (int endY = 0; endY < COLUMN; endY++)
					{
						if (board[endX][endY] == whoPlayer && cm.hasNextMove(board,endX,endY,whoPlayer))	//终点坐标并且得含有下一步可走空棋
						{
							Board<int> tempBoard(board);
							solveRedAndBlue srab(&tempBoard, whoPlayer, startX, startY, endX, endY);
							if (srab.solve()){
								return maxLength;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

//得到后手的最长连接步
int FinalAlgorithm::getMaxLengthLeftToRight(int board[][COLUMN], int whoPlayer){
	for (int maxLength = 10; maxLength > 0; maxLength--)//连接步长度
	{
		for (int startY = 0; startY < COLUMN - maxLength; startY++)	//起始行
		{
			for (int startX = 0; startX < ROW; startX++)//起始列
			{
				if (board[startX][startY] == whoPlayer && cm.hasUpMove(board,startX,startY,whoPlayer))		//起始坐标
				{
					Board<int> tempBoard(board);
					isHasPathWillMustWin hpwm(&tempBoard, whoPlayer);
					if (hpwm.solveIsCanPut2(startX, startY))
					{
						int endY = startY + maxLength;
						for (int endX = 0; endX < ROW; endX++)
						{
							if (board[endX][endY] == whoPlayer&& cm.hasNextMove(board, startX, startY, whoPlayer))	//终点坐标
							{
								Board<int> tempBoard(board);
								isHasPathWillMustWin hpwm(&tempBoard, whoPlayer);
								if (hpwm.solveIsCanPut(endX, endY)){
									Board<int> tempBoard(board);
									solveRedAndBlue srab(&tempBoard, whoPlayer, startX, startY, endX, endY);
									if (srab.solveWillArriveMaxLength()){
										if (cm.isValid(startX, startY - 1) && Computer::board[startX][startY - 1] == NO_CHESS
											&&cm.isValid(startX + 1, startY - 1) && Computer::board[startX + 1][startY - 1] == NO_CHESS){
											maxLength += 1;
										}
										if (cm.isValid(endX, endY + 1) && Computer::board[endX][endY + 1] == NO_CHESS
											&&cm.isValid(endX - 1, endY + 1) && Computer::board[endX - 1][endY + 1] == NO_CHESS){
											maxLength += 1;
										}
										return maxLength;
									}
								}
								
							}
						}
					}
					
				}
			}
		}
	}
	return 0;
}

//得到后手实际的最长连接步
int FinalAlgorithm::getMaxLengthLeftToRight_Actual(int board[][COLUMN], int whoPlayer){
	for (int maxLength = 10; maxLength > 0; maxLength--)//连接步长度
	{
		for (int startY = 0; startY < COLUMN - maxLength; startY++)	//起始行
		{
			for (int startX = 0; startX < ROW; startX++)//起始列
			{
				if (board[startX][startY] == whoPlayer&& cm.hasUpMove(board,startX,startY,whoPlayer))		//起始坐标
				{
					int endY = startY + maxLength;
					for (int endX = 0; endX < ROW; endX++)
					{
						if (board[endX][endY] == whoPlayer && cm.hasNextMove(board,endX,endY,whoPlayer))	//终点坐标
						{
							Board<int> tempBoard(board);
							solveRedAndBlue srab(&tempBoard, whoPlayer, startX, startY, endX, endY);
							if (srab.solve()){
								return maxLength;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

Location FinalAlgorithm::getBestLocation(vector<Location> locations, int whoPlayer)
{
	vector<vector<Location>> locationsVec;
	vector<Location> arr;
	Location location;
	computeAllChoices(locations, locations.size(), locationsVec, 0, K, arr, 0);		//得到所有组合
	updateLocationsScore(locationsVec, whoPlayer, locations);
	if (locations.size() <= 0)
	{
		return location;
	}
	location = locations.at(0);
	for (int i = 1; i < locations.size(); i++)
	{
		
		if (locations.at(i).getScore() > location.getScore())
		{
			location = locations.at(i);
		}
	}
	return location;
}

//被选取集合  长度  存结果的集合 0 选取个数 
void  FinalAlgorithm::computeAllChoices(std::vector<Location> &data, int n, vector<vector<Location>>& locationsVec, 
	int startIndex, int m, vector<Location>& arr, int arrIndex)
{
	if (m == 0)
	{
		locationsVec.push_back(arr);
		return;
	}

	int endIndex = n - m;
	for (int i = startIndex; i <= endIndex; i++)
	{
		arr.push_back(data.at(i));
		computeAllChoices(data, n, locationsVec, i + 1, m - 1, arr, arrIndex + 1);
		arr.pop_back();
	}
}

/*
得到locations中选取number个位置的所有组合
*/
vector<vector<Location>> FinalAlgorithm::getCombsByEmptyChess(vector<vector<Location>>& locationsVec, vector<Location> locations, int number)
{
	if (locationsVec.size() == 0)
	{
		for (int i = 0; i < locations.size(); i++)
		{
			vector<Location> tempLocations;
			tempLocations.push_back(locations.at(i));
			locationsVec.push_back(tempLocations);
		}
		bool contin = false;
		for (int i = 0; i < locationsVec.size(); i++)
		{
			if (locationsVec.at(i).size() < number)
			{
				contin = true;
				break;
			}
		}
		if (contin)
		{
			getCombsByEmptyChess(locationsVec, locations, number);
		}
		return locationsVec;
	}
	else
	{
		for (int i = 0; i < locationsVec.size(); i++)
		{
			vector<Location> temp = locationsVec.at(i);		//记录当前
			bool enter = false;
			for (int j = 0; j < locations.size(); j++)
			{
				bool flag = true;
				for (int m = 0; m < temp.size(); m++)
				{	//判断是否存在
					if (temp.at(m) == locations.at(j))
					{
						flag = false;
					}
				}
				if (flag)
				{
					if (!enter)
					{
						locationsVec.at(i).push_back(locations.at(j));
						enter = true;
					}
					else
					{
						vector<Location> tempLocations;
						for (int n = 0; n < temp.size(); n++)
						{
							tempLocations.push_back(temp.at(n));
						}
						tempLocations.push_back(locations.at(j));
						locationsVec.push_back(tempLocations);
					}
				}
			}
		}
		bool contin = false;
		for (int i = 0; i < locationsVec.size(); i++)
		{
			if (locationsVec.at(i).size() < number)
			{
				contin = true;
			}
		}
		if (contin)
		{
			getCombsByEmptyChess(locationsVec, locations, number);
		}
		return locationsVec;
	}
}
