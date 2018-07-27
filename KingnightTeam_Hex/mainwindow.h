#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include"chessboard.h"
#include"handle.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ChessBoard *chessBoard;     //棋盘
    Handle *handle;      //功能区
    QGridLayout *mainLayout;        //主面板

};

#endif // MAINWINDOW_H
