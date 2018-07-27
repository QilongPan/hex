#ifndef SOLVEREDANDBLUE_H  
#define SOLVEREDANDBLUE_H  
#include <stack>
#include"hexdefine.h"
#include"dfs.h"
#include"Location.h"
using namespace std;

class solveRedAndBlue
{
public:
	solveRedAndBlue(Board<int> *_board, int type,int startX,int startY,int endX,int endY) : _board(_board), type(type), 
		startX(startX), startY(startY), endX(endX), endY(endY) {

	}
	~solveRedAndBlue() {}

	bool solve() {
		// 寻找x = 0的点
		moves.push(Location(startX, startY));
		return dfs_solve();
	}

	bool solveWillArriveMaxLength()
	{
		moves.push(Location(startX, startY));
		return dfs_willSolve();
	}
private:
	inline void add_neighbor(int x, int y) {
		if (_board->legal(x, y) && _board->at(x, y) == type && !history.at(x, y))
		{
			moves.push(Location(x, y));
			history.at(x, y) = true;
		}
	}

	inline void add_Bridge(int x, int y)
	{
		moves.push(Location(x, y));
		history.at(x, y) = true;
	}

	// 自上向下搜索
	bool dfs_solve() {
		if (moves.size() == 0) { return  false; }
		Location &current_move = moves.top();
		// 当找到x = 10的点
		if (current_move.getX() == endX && current_move.getY() == endY) { return true; }
		int x = current_move.getX(),
			y = current_move.getY();
		moves.pop();
		add_neighbor(x - 1, y);
		add_neighbor(x - 1, y + 1);
		add_neighbor(x, y - 1);
		add_neighbor(x, y + 1);
		add_neighbor(x + 1, y - 1);
		add_neighbor(x + 1, y);
		return dfs_solve();
	}

	bool dfs_willSolve(){
		if (moves.size() == 0) { return  false; }
		Location &current_move = moves.top();
		if (current_move.getX() == endX && current_move.getY() == endY) { return true; }
		int x = current_move.getX(),
			y = current_move.getY();
		moves.pop();
		add_neighbor(x - 1, y);
		add_neighbor(x - 1, y + 1);
		add_neighbor(x, y - 1);
		add_neighbor(x, y + 1);
		add_neighbor(x + 1, y - 1);
		add_neighbor(x + 1, y);
		//上
		if (_board->legal(x - 1, y) && _board->at(x - 1, y) == NO_CHESS
			&& _board->legal(x - 1, y + 1) && _board->at(x - 1, y + 1) == NO_CHESS
			&& _board->legal(x - 2, y + 1) && _board->at(x - 2, y + 1) == type && !history.at(x - 2, y + 1)){
			add_Bridge(x - 2, y + 1);
		}
		//右上
		if (_board->legal(x - 1, y + 1) && _board->at(x - 1, y + 1) == NO_CHESS
			&& _board->legal(x, y + 1) && _board->at(x, y + 1) == NO_CHESS
			&& _board->legal(x - 1, y + 2) && _board->at(x - 1, y + 2) == type && !history.at(x - 1, y + 2)){
			add_Bridge(x - 1, y + 2);
		}
		//右下
		if (_board->legal(x, y + 1) && _board->at(x, y + 1) == NO_CHESS
			&& _board->legal(x + 1, y) && _board->at(x + 1, y) == NO_CHESS
			&& _board->legal(x + 1, y + 1) && _board->at(x + 1, y + 1) == type && !history.at(x + 1, y + 1)){
			add_Bridge(x + 1, y + 1);
		}
		//下
		if (_board->legal(x + 1, y - 1) && _board->at(x + 1, y - 1) == NO_CHESS
			&& _board->legal(x + 1, y) && _board->at(x + 1, y) == NO_CHESS
			&& _board->legal(x + 2, y - 1) && _board->at(x + 2, y - 1) == type && !history.at(x + 2, y - 1)){
			add_Bridge(x + 2, y - 1);
		}
		//左下
		if (_board->legal(x, y - 1) && _board->at(x, y - 1) == NO_CHESS
			&& _board->legal(x + 1, y - 1) && _board->at(x + 1, y - 1) == NO_CHESS
			&& _board->legal(x + 1, y - 2) && _board->at(x + 1, y - 2) == type && !history.at(x + 1, y - 2)){
			add_Bridge(x + 1, y - 2);
		}
		//左上
		if (_board->legal(x - 1, y) && _board->at(x - 1, y) == NO_CHESS
			&& _board->legal(x, y - 1) && _board->at(x, y - 1) == NO_CHESS
			&& _board->legal(x - 1, y - 1) && _board->at(x - 1, y - 1) == type && !history.at(x - 1, y - 1)){
			add_Bridge(x - 1, y - 1);
		}
		return dfs_willSolve();
	}

	stack<Location> moves;
	int type;
	int startX;
	int startY;
	int endX;
	int endY;
	Board<bool> history;
	Board<int> *_board;
};
#endif //XXXX_H 