#ifndef UCTNODE_H
#define UCTNODE_H
#include"uctmove.h"
#include<vector>
#include<iostream>
using namespace std;
class UCTNode
{
public:
    UCTNode();
    //子节点
    vector<UCTNode> child;
    //总访问数
    int visit;
    //胜利局数
    int win;
    //作为子节点的临时着法
    UCTMove move;
    //作为根节点的最佳着法
    UCTMove bestMove;
};

#endif // UCTNODE_H
