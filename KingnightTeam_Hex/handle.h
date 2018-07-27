#ifndef HANDLE_H
#define HANDLE_H

#include <QWidget>
#include<QPushButton>
#include<QRadioButton>
#include<QGridLayout>
#include<QFileDialog>
#include<QFile>
#include<QDebug>
#include<QLineEdit>
#include<QList>
#include<QString>
#include<QThread>
#include"chessboard.h"


namespace Ui {
class Handle;
}

class Handle : public QWidget
{
    Q_OBJECT

public:
    explicit Handle(QWidget *parent = 0);
    ~Handle();
     Play play = Play();
     Transform tf;
     void initBoard(int board[][COLUMN]);       //初始化棋盘
     void initBoardPicture(QPushButton* btn[][COLUMN]);   //初始化棋盘图片

private:
    Ui::Handle *ui;
    QPushButton *startButton;   //开始
    QPushButton *restartButton; //重新开始
    QPushButton *backButton;    //悔棋
    QRadioButton *playerButton;    //选手先手
    QRadioButton *computerButton;   //电脑先手
    QPushButton *chooseFile;        //选择棋谱
    QPushButton *saveFile;      //保存棋谱
    QPushButton *upBtn;        //前进按钮
    QPushButton *downBtn;//后退按钮
    QPushButton  *toBtn; //跳转按钮
    QLineEdit *stepNumberEdit;  //跳转文本框
    QGridLayout *rightLayout;   //布局方式

public slots:
    void startBtnClick();       //点击开始按钮
    void restartBtnClick();     //点击重新开始按钮事件
    void backBtnClick();        //点击悔棋按钮事件
    void radioBtnClick_Computer();       //点击电脑单选按钮事件
    void radioBtnClick_Player();        //点击选手单选按钮事件
    void readBtnClick();
    void saveBtnClick();
    void toBtnClick();//跳转
    void upBtnClick();
    void downBtnClick();

};

#endif // HANDLE_H
