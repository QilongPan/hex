#include "negativemaxminsearch.h"

NegativeMaxMinSearch::NegativeMaxMinSearch()
{

}

NegativeMaxMinSearch::NegativeMaxMinSearch(int board[][COLUMN]){
   for(int i = 0 ; i < ROW ; i++){
       for(int j =0 ; j < COLUMN; j++){
           pieces[i][j] = board[i][j];
       }
   }
}

void NegativeMaxMinSearch::search(){
    int depth = SEARCH_DEPTH ;	//搜索深度
    Move moveTem = Move();
    moveTem.setMoveDirection(COMPUTER_CHESS);
    search_NegativeMinimaxValue(depth,moveTem,pieces);
}

//负极大极小值搜索算法
int NegativeMaxMinSearch::search_NegativeMinimaxValue(int depth,Move move,int board[][COLUMN]){
    int bestValue = -200;	//指定一个负无穷的初始值
    int value;
    //棋局结束
   /* if(jiw.isWin(board,COMPUTER_CHESS)
            || jiw.isWin(board,PLAYER_CHESS)){
        return 20000;       //返回极大值
    }*/
  /*  if(jiw.isWin(board,COMPUTER_CHESS)){
        return 20000;
    }
    if(jiw.isWin(board,PLAYER_CHESS)){
        return -20000;
    }*/
    //叶子节点取估值
    if(depth <= 0){
        if(isComputerOnLastDepth(SEARCH_DEPTH - depth)){
            return evaluation(board,COMPUTER_CHESS);
        }
        else{
            return evaluation(board,PLAYER_CHESS);
        }
    }
    //得到所有的走法,根据第几层
    vector<Move> moves =
            getAllMove((SEARCH_DEPTH - depth) % 2 == 0
            ?COMPUTER_CHESS:PLAYER_CHESS,board);
    for(int i = 0 ; i < moves.size() ; i++){
        //产生当前局面
        makeMove(moves.at(i), board);//产生第i个局面
        value = -search_NegativeMinimaxValue(depth-1,moves.at(i),board);
        //恢复当前局面
        unMakeMove(moves.at(i), board);
        if(value > bestValue){
            bestValue = value;
            if(depth == SEARCH_DEPTH)
                bestMove = moves.at(i);
        }
    }
    return bestValue;	//返回最大/最小值
}


//判断搜索的最后一层是不是电脑
bool NegativeMaxMinSearch::isComputerOnLastDepth(int depth){
    if(depth % 2 == 0){
        return false;
    }
    return true;
}

//得到所有的走步
vector<Move> NegativeMaxMinSearch::getAllMove(int moveDirection,int board[][COLUMN]){
    vector<Move> moves;
    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            if(board[i][j] == NO_CHESS){
                Move move ;
                Location location ;
                location.setX(i);
                location.setY(j);
                move.setLocation(location);
                //设置该走步为电脑还是选手的
                move.setMoveDirection(moveDirection);
                moves.push_back(move);
            }
        }
    }
    return moves;
}

//产生局面
void NegativeMaxMinSearch ::makeMove(Move move ,int board[][COLUMN]){
    if(move.getMoveDirection() == COMPUTER_CHESS){
        board[move.getLocation().getX()][move.getLocation().getY()]
                =COMPUTER_CHESS;
    }
    else{
        board[move.getLocation().getX()][move.getLocation().getY()]
                =PLAYER_CHESS;
    }
}
//恢复局面
void NegativeMaxMinSearch::unMakeMove(Move move,int board[][COLUMN]){
    board[move.getLocation().getX()][move.getLocation().getY()]
            = NO_CHESS;
}
//评估函数
int NegativeMaxMinSearch::evaluation(int board[][COLUMN],int whoPlayer){
    int maxLength1 ;        //电脑
    int maxLength2;//选手
  /*  if(Computer::onTheOffensiveValue == whoPlayer){
        if(whoPlayer == COMPUTER_CHESS){
            maxLength1 = ftlsc.getMaxLength_TopToBottom(board,whoPlayer);
            maxLength2 = ftlsc.getMaxLength_LeftToRight(board,PLAYER_CHESS);
        }
        else{
            maxLength2 = ftlsc.getMaxLength_TopToBottom(board,whoPlayer);
            maxLength1 = ftlsc.getMaxLength_LeftToRight(board,COMPUTER_CHESS);
        }

    }
    else{
        if(whoPlayer == COMPUTER_CHESS){
            maxLength2 = ftlsc.getMaxLength_TopToBottom(board,PLAYER_CHESS);
            maxLength1 = ftlsc.getMaxLength_LeftToRight(board,whoPlayer);
        }
        else{
            maxLength1 = ftlsc.getMaxLength_TopToBottom(board,COMPUTER_CHESS);
            maxLength2 = ftlsc.getMaxLength_LeftToRight(board,whoPlayer);
        }
    }
    if(whoPlayer == PLAYER_CHESS){
        return (maxLength1-maxLength2)*10;
    }
    else{
        return (maxLength2-maxLength1)*10;
    }*/
  /*  if(whoPlayer == Computer::onTheOffensiveValue){
        maxLength1 = ftlsc.getMaxLength_TopToBottom(board,whoPlayer);
        maxLength2 = ftlsc.getMaxLength_LeftToRight(board,getOtherPlayer(whoPlayer));
    }
    else{
        maxLength2 = ftlsc.getMaxLength_TopToBottom(board,getOtherPlayer(whoPlayer));
        maxLength1 = ftlsc.getMaxLength_LeftToRight(board,whoPlayer);
    }
    int value1 = maxLength1*10;
    int value2 = maxLength2*10;
    if(Computer::onTheOffensiveValue == COMPUTER_CHESS){
        if(whoPlayer == COMPUTER_CHESS){
            return value1 - value2;
        }
        else{
            return value2 - value1;
        }
    }
    //选手为先手
    else{
        if(whoPlayer == COMPUTER_CHESS){
            return value2 - value1;
        }
        else{
            return value1 - value2;
        }
    }*/
	int value1 = ctm.getFord(board, COMPUTER_CHESS);
	int value2 = ctm.getFord(board, PLAYER_CHESS);
	if (Computer::onTheOffensiveValue == COMPUTER_CHESS)
	{
		if (whoPlayer == COMPUTER_CHESS)
		{
			return value1 ;
		}
		else
		{
			return value2;
		}
	}
	
}

Move NegativeMaxMinSearch::getMove(){
    return bestMove;
}

//得到另一家选手
int NegativeMaxMinSearch::getOtherPlayer(int whoPlayer){
    if(whoPlayer == COMPUTER_CHESS){
        return PLAYER_CHESS;
    }
    else{
        return COMPUTER_CHESS;
    }
}


