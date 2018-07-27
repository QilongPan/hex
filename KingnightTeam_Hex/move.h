#ifndef MOVE_H
#define MOVE_H
#include"location.h"

class Move
{
public:
    Move();
    Move(Location newLocation,int newMoveDirection);
    void setLocation(Location to);
    Location getLocation();
    void setScore(int score);
    int getScore();
    void setMoveDirection(int moveDirection);
    int getMoveDirection();
private:
    Location to;	//坐标
    int score;	//走法的分数
    int moveDirection;  //方向
};

#endif // MOVE_H
