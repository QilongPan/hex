#include "alphabetasearch.h"

AlphaBetaSearch::AlphaBetaSearch()
{

}

AlphaBetaSearch::AlphaBetaSearch(int pieces[][COLUMN]){
    //初始化棋盘
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COLUMN; j++){
            board[i][j] = pieces[i][j];
        }
    }
}

//alpha取极小，beta取极大
int AlphaBetaSearch::search_AlphaBeta(int depth, int nAlpha, int nBeta){
    int value;
	//判断是否有赢得局面
	int result = isWillWin(board);
	if (result > 0){
		return evaluation(board,getPlayer(depth));
	}
    if (depth <= 0){
		return evaluation(board, getPlayer(depth));
    }
    //得到所有的走法,根据第几层
    vector<Move> moves = getAllMove(board);
    for (int i = 0; i < moves.size(); i++){
        makeMove(moves.at(i), board,getPlayer(depth));
        value = -search_AlphaBeta(depth - 1, -nBeta, -nAlpha);
        unMakeMove(moves.at(i), board);
		if (value > nAlpha){
			nAlpha = value;
			if (depth == ALPHABETASEARCHDEPTH){
				move = moves.at(i);
			}
		}
        if (value >= nBeta){        //剪枝情况判断
			break;
        }
    }
    return nAlpha;	//返回最大/最小值
}

//得到所有的走步
vector<Move> AlphaBetaSearch::getAllMove(int board[][COLUMN]){
    vector<Move> moves;
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COLUMN; j++){
            if (board[i][j] == NO_CHESS){
                Move move;
                Location location;
                location.setX(i);
                location.setY(j);
                move.setLocation(location);
                moves.push_back(move);
            }
        }
    }
    return moves;
}

//产生局面
void AlphaBetaSearch::makeMove(Move move, int board[][COLUMN],int whoPlayer){
	board[move.getLocation().getX()][move.getLocation().getY()] = whoPlayer;
}

//恢复局面
void AlphaBetaSearch::unMakeMove(Move move, int board[][COLUMN]){
    board[move.getLocation().getX()][move.getLocation().getY()] = NO_CHESS;
}


//评估函数
int AlphaBetaSearch::evaluation(int board[][COLUMN], int whoPlayer){
	int computerValue = 0;
	int playerValue = 0;
	int result = isWillWin(board);
	if (result == COMPUTER_WIN){
		if (whoPlayer == COMPUTER_CHESS){
			return 10000;
		}
		else{
			return -10000;
		}
	}
	else if (result == PLAYER_WIN){
		if (whoPlayer == COMPUTER_CHESS){
			return -10000;
		}
		else{
			return 10000;
		}
	}
	else if(result == DRAW){
		return 0;
	}

//	computerValue = computerValue + fa.getMaxLength_Actual(board, COMPUTER_CHESS);
	computerValue = computerValue +fa.getMaxLength(board, COMPUTER_CHESS);
//	playerValue = playerValue +  fa.getMaxLength_Actual(board, PLAYER_CHESS);
	playerValue = playerValue + fa.getMaxLength(board, PLAYER_CHESS);

	if (whoPlayer == COMPUTER_CHESS){
		if (computerValue - playerValue > 0){
			return computerValue;
		}
		else{
			return -playerValue;
		}
	}
	else{
		if (computerValue - playerValue >= 0){
			return -computerValue;
		}
		else{
			return playerValue;
		}
	}
}
//得到另一家选手
int AlphaBetaSearch::getOtherPlayer(int whoPlayer){
    if (whoPlayer == COMPUTER_CHESS){
        return PLAYER_CHESS;
    }
    else{
        return COMPUTER_CHESS;
    }
}

bool AlphaBetaSearch::isWin(int board[][COLUMN]){
	if (jiw.isWin(board, COMPUTER_CHESS)){
		return COMPUTER_WIN;
	}
	if (jiw.isWin(board, PLAYER_CHESS)){
		return PLAYER_WIN;
	}
	bool flag = true;
	for (int i = 0; i < ROW; ++i){
		for (int j = 0; j < COLUMN; ++j){
			if (board[i][j] == NO_CHESS){
				flag = false;
				break;
			}
		}
		if (flag){
		}
		else{
			break;
		}
	}
	if (flag){
		return DRAW;
	}
	else{
		return NORESULT;
	}
}

bool AlphaBetaSearch::isWillWin(int board[][COLUMN]){
	if (jiw.isWillMustWin(board, COMPUTER_CHESS)){
		return COMPUTER_WIN;
	}
	if (jiw.isWillMustWin(board, PLAYER_CHESS)){
		return PLAYER_WIN;
	}
	bool flag = true;
	for (int i = 0; i < ROW; ++i){
		for (int j = 0; j < COLUMN; ++j){
			if (board[i][j] == NO_CHESS){
				flag = false;
				break;
			}
		}
		if (flag){
		}
		else{
			break;
		}
	}
	if (flag){
		return DRAW;
	}
	else{
		return NORESULT;
	}
}
int AlphaBetaSearch::getPlayer(int depth){
	if ((ALPHABETASEARCHDEPTH - depth) % 2 == 0){
		return COMPUTER_CHESS;
	}
	else{
		return PLAYER_CHESS;
	}
}

//判断搜索的最后一层是不是电脑
bool AlphaBetaSearch::isComputerOnLastDepth(int depth){
	if (depth % 2 == 0){
		return false;
	}
	return true;
}