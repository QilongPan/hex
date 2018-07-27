#ifndef LOCATION_H
#define LOCATION_H

/*
棋盘的位置类
*/
class Location
{
public:
    Location();
    Location(int x,int y);
    void setX(int x);
    void setY(int y);
	void setScore(int score);
    int getX();
    int getY();
	int getScore();
	bool operator== (Location loc);
private:
    int x;      //横坐标
    int y;      //纵坐标
	int score;	//分数
};

#endif // LOCATION_H
