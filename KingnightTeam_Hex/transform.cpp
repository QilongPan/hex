#include "transform.h"

Transform::Transform()
{

}
//将字符串转换为整数
int Transform::getInt(string strText){
    int n = 0;
    stringstream os;
    os << strText;
    os >> n;
    return n;
}
//将坐标转换为输出
string Transform::getInputString(int x, int y){
    string str = getString(x);
    str.append(" ");
    str.append(getString(y));
    return str;
}

//将整数转换为字符串
string Transform::getString(int n)
{
    string s;
    stringstream os;
    os << n;
    os >> s;
    return s;
}

//判断下棋位置是否合法
bool Transform::judgeIndexIsValid(int x, int y){
  if(x<0 || y<0 ||x>10 ||y>10){
      return false;
  }
  else{
      return Computer::board[x][y] == NO_CHESS?true:false;
  }

}

