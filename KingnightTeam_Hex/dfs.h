#ifndef DFS_H
#define DFS_H
#include <stack>
#include"hexdefine.h"
#include"Location.h"
using namespace std;
template <typename _Ty>
class Board
{
public:
    Board() : _board() {
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COLUMN; ++j)
            {
                _board[i][j] = 0;
            }
        }
    }
    // 从外部导入棋盘矩阵
    Board(const _Ty __board[11][11]) {
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COLUMN; ++j)
            {
                _board[i][j] = __board[i][j];
            }
        }
    }

    ~Board() {}

    bool legal(int x, int y) {
        return !(x < 0 || x > 10 || y < 0 || y > 10);
    }

    _Ty &at(int x, int y) {
        return _board[x][y];
    }
private:
    _Ty _board[ROW][COLUMN];
};


class redDFS
{
public:
    redDFS(Board<int> *_board, int type) : _board(_board), type(type) {

    }
    ~redDFS() {}

    bool solve() {
        // 寻找x = 0的点
        for (int j = 0; j < COLUMN; ++j)
        {
            if (_board->at(0, j) == type)
            {
                moves.push(Location(0, j));
            }
        }

        return dfs_find();
    }

	
private:
    inline void add_neighbor(int x, int y) {
        if (_board->legal(x, y) && _board->at(x, y) == type && !history.at(x, y))
        {
            moves.push(Location(x, y));
            history.at(x, y) = true;
        }
    }
    // 自上向下搜索
    bool dfs_find() {
        if (moves.size() == 0) { return  false; }
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
        return dfs_find();
    }

	
    stack<Location> moves;
    int type;
    Board<bool> history;
    Board<int> *_board;
};

class blueDFS
{
public:
    blueDFS(Board<int> *_board, int type) : _board(_board), type(type) {

    }
    ~blueDFS() {}

    bool solve() {
        // 寻找x = 0的点
        for (int j = 0; j < ROW; ++j)
        {
            if (_board->at(j, 0) == type)
            {
                moves.push(Location(j, 0));
            }
        }
        return dfs_find();
    }
private:
    inline void add_neighbor(int x, int y) {
        if (_board->legal(x, y) && _board->at(x, y) == type && !history.at(x, y))
        {
            moves.push(Location(x, y));
            history.at(x, y) = true;
        }
    }
    // 自上向下搜索
    bool dfs_find() {
        if (moves.size() == 0) { return  false; }
        Location &current_move = moves.top();
        // 当找到x = 10的点
        if (current_move.getY() == (COLUMN - 1)) { return true; }
        int x = current_move.getX(),
            y = current_move.getY();
        moves.pop();
        add_neighbor(x - 1, y);
        add_neighbor(x - 1, y + 1);
        add_neighbor(x, y - 1);
        add_neighbor(x, y + 1);
        add_neighbor(x + 1, y - 1);
        add_neighbor(x + 1, y);
        return dfs_find();
    }

    stack<Location> moves;
    int type;
    Board<bool> history;
    Board<int> *_board;
};

#endif // DFS_H
