#include "findthelongeststepconnection.h"

/*
 *寻找最长连接步
 */
FindTheLongestStepConnection::FindTheLongestStepConnection()
{

}

//判断棋盘中能走的最多的连接步(从上到下）
int FindTheLongestStepConnection::getMaxLength_TopToBottom( int board[][COLUMN],int whoPlayer){
    int moveLength = 0;	//最长连接步的长度
    //得到递归的数组
    for(int startX = 0; startX< 11 ; startX++){
        for(int startY = 0 ; startY < 11 ; startY++){	//寻找一个起始点
            if(board[startX][startY] == whoPlayer){
          //      connectStepNumber=0;
                for(int endX = 10; endX > startX ; endX--){
                    for(int endY = 0 ; endY < 11 ; endY++){
                        if(board[endX][endY] == whoPlayer){
                            moveLength = startPath(board,startX,startY,endX,endY,whoPlayer);
                            if(moveLength != -1){
                                return moveLength;
                            }
                        }
                    }
                }
            }
        }
    }
    return moveLength ;
}


//判断某点到某点是否连通
int FindTheLongestStepConnection::startPath( int board[][COLUMN] ,int startX ,int startY,int endX,int endY,int whoPlayer) {
  //得到递归的数组
    int ** array;
    array = new int *[ROW];
    for(int i = 0; i < ROW; i ++)
        array[i] = new int[COLUMN];
    getRecursiveArray(array,whoPlayer,board);
    FindAChannel fa = FindAChannel(array);

    if(fa.isConnected(startX,startY,endX,endY)){
        if(whoPlayer == Computer::onTheOffensiveValue){
            return endX-startX;     //从上到下
        }
        else{
            return endY-startY;     //从左到右
        }
    }
    return -1;
/*	Board<int> tempBoard(board);
	solveRedAndBlue srab(&tempBoard, whoPlayer, startX, startY, endX, endY);
	if (srab.solve()){
		if (whoPlayer == Computer::onTheOffensiveValue){
			return endX - startX;     //从上到下
		}
		else{
			return endY - startY;     //从左到右
		}
	}
	return -1;*/
}


//得到递归的数组,返回一个0,1数组，当没有棋或是其他方的棋，设置为-1 2017/1/15
void FindTheLongestStepConnection::getRecursiveArray(int** array,int whoPlayer,int board[][COLUMN]){
    //得到递归的数组
    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN; j++){
            if(board[i][j] == whoPlayer){
                array[i][j] = PASS;		//将自己的棋设为可走
            }
            else{
                array[i][j] = NO_PASS;	//将其余的棋设为不可走
            }
        }
    }
}

//判断棋盘中能走的最多的连接步(从左到右）
int FindTheLongestStepConnection::getMaxLength_LeftToRight(int board[][COLUMN],int whoPlayer){
  //  ArrayList<Integer> list = new ArrayList<Integer>();
    int moveLength = 0;	//最长连接步的长度
 //   int connectStepNumber = 0 ;	//最长连接步的数量
 //   boolean flag = false;
    for(int startY = 0; startY< 11 ; startY++){
        for(int startX = 0 ; startX < 11 ; startX++){	//寻找一个起始点
            if(board[startX][startY] == whoPlayer){
            //    connectStepNumber=0;
                for(int endY = 10; endY > startY ; endY--){
                    for(int endX = 0 ; endX < 11 ; endX++){
                        if(board[endX][endY] == whoPlayer){
                            moveLength = startPath(board,startX,startY,endX,endY,whoPlayer);
                            //返回末尾点的多少
                        /*    if(moveLength != -1){
                                int nullSpace = getAnEmptyPlaceNumberNearIndex(endX, endY, board);

                                if(nullSpace > 0){
                                    flag = true;
                                    if(connectStepNumber == 0){
                                        list.add(moveLength);
                                        list.add(nullSpace);
                                    }
                                    connectStepNumber++;
                                }
                            }*/
                            if(moveLength != -1){
                                return moveLength;
                            }
                        }
                    }
                  /*  if(flag){
                        list.add(connectStepNumber);
                        return list;
                    }*/
                }
            }
        }
    }
    return moveLength ;
}


