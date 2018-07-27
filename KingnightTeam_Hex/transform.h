#ifndef TRANSFORM_H
#define TRANSFORM_H
#include<string>
#include<iostream>
#include <sstream>
#include"computer.h"
using namespace std;

class Transform
{
public:
    Transform();
    string getInputString(int x, int y);        //将坐标转换为输出语句
    string getString(int n);        //将整数装换为字符串
    int getInt(string strText); //将字符串转换为数字
    bool judgeIndexIsValid(int x, int y);//判断下标位置是否合法
};

#endif // TRANSFORM_H
