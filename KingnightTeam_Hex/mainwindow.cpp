#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(QSize(1200,600));
    mainLayout = new QGridLayout;
    chessBoard = new ChessBoard(this);
    handle = new Handle(this);
    handle->setGeometry(800,0,300,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

