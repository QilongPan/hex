#include "move.h"

Move::Move()
{

}

Move::Move(Location newLocation, int newMoveDirection){
    to = newLocation;
    moveDirection = newMoveDirection;
}

void Move::setLocation(Location to){
    this->to = to;
}

Location Move::getLocation(){
    return to;
}

void Move::setScore(int score){
    this->score = score;
}

int Move::getScore(){
    return score;
}

void Move::setMoveDirection(int moveDirection){
    this->moveDirection = moveDirection;
}

int Move::getMoveDirection(){
    return moveDirection;
}
