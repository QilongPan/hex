#ifndef PLAY_H
#define PLAY_H
#include<string>
#include<iostream>
#include"computer.h"
#include"uctsearch.h"
#include"playchess_start.h"
#include"alphabetasearch.h"
#include"finalalgorithm.h"
#include"transform.h"
class Play
{
public:
    Play();
    UctSearch us;           //uct搜索
    UCTMove move;
    PlayChess_Start ps;          //经验下棋（开局库)
    Transform tf ;                //转换
    AlphaBetaSearch abs;        //alphabeta搜索
    FinalAlgorithm fa;      //终局算法
    string playChess();     //下棋
};

#endif // PLAY_H0
