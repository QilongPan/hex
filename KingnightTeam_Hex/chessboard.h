#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include<QPushButton>
#include<QMessageBox>
#include<QLabel>
#include<string>
#include"hexdefine.h"
#include"computer.h"
#include"play.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
	Play play;
	Transform tf;
	JudgeIsWin jiw;
    void paintEvent(QPaintEvent *event); 
    void initButtonPicture();        
    int getXByMouse(QPushButton *btn);     //根据鼠标点击位置获得x坐标
    int getYByMouse(QPushButton *btn,int x);     //根据鼠标点击位置获得y坐标
    static QPushButton *btn[ROW][COLUMN];       // 棋盘btn
   
private:
    Ui::ChessBoard *ui;


public slots:
    void onButtonPictureClick();        //按钮点击事件
};

#endif // CHESSBOARD_H
