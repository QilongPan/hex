#include "findachannel.h"
/*
 * 判断两点是否连通
*/
FindAChannel::FindAChannel()
{

}

FindAChannel::FindAChannel(int** board){

    this->board = board;
    count = 0;
}

//判断两个点之间是否连接
bool FindAChannel::isConnected(int startX , int startY,int endX,int endY){
    recursionGetPath(startX ,startY,endX,endY) ;
    if(count >0){
        return true;
    }
    else{
        return false;
    }
	
}

//得到两点连通的路径数量
void FindAChannel::recursionGetPath(int startX , int startY,int endX,int endY) {
    board[startX][startY] =ALREADY_PASS;
    if(startX == endX && startY == endY) {
        count++;
    }
    //朝右
    if(isCorrectIndex(startX,startY+1)
            && board[startX][startY+1]
                    == PASS
            )
        recursionGetPath(startX,startY+1,endX,endY);
    //朝下
    if(isCorrectIndex(startX+1,startY)
            && board[startX+1][startY]
                    ==PASS)
        recursionGetPath(startX+1,startY,endX,endY);
    //朝左
    if(isCorrectIndex(startX,startY-1)
            && board[startX][startY-1]
                    == PASS)
        recursionGetPath(startX,startY-1,endX,endY);
    //朝上
    if(isCorrectIndex(startX-1,startY)
            && board[startX-1][startY]
                    == PASS)
        recursionGetPath(startX-1,startY,endX,endY);
    //朝右上
    if(isCorrectIndex(startX-1,startY+1)
            && board[startX-1][startY+1]
                    ==PASS){
        recursionGetPath(startX-1,startY+1,endX,endY);
    }
    //朝左下
    if(isCorrectIndex(startX+1,startY-1)
            && board[startX+1][startY-1]
                    == PASS){
        recursionGetPath(startX+1,startY-1,endX,endY);
    }
    board[startX][startY] = PASS;
}



//判断坐标是否越界
bool FindAChannel::isCorrectIndex(int x, int y){
    if(x >= ROW
            || x < 0
            ||y < 0
            ||y >= COLUMN){
        return false;
    }
    return true;
}
