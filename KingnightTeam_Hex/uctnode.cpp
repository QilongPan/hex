#include "uctnode.h"

UCTNode::UCTNode()
{
    visit = 0;  //访问次数
    win = 0;    //赢得次数
    move.x = -1;
    move.y = -1;
}
