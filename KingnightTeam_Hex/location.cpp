#include "location.h"


Location::Location()
{

}

Location::Location(int x,int y){
    this->x = x;
    this->y = y;
}

void Location::setX(int x){
    this->x = x;
}

void Location::setY(int y){
    this->y = y;
}

void Location::setScore(int score){
	this->score = score;
}

int Location::getX(){
    return x;
}

int Location::getY(){
    return y;
}

int Location::getScore(){
	return score;
}

bool Location::operator==(Location loc){
	if (loc.getX() == x && loc.getY() == y)
	{
		return true;
	}
	return false;
}