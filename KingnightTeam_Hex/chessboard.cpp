#include "chessboard.h"
#include "ui_chessboard.h"

QPushButton* ChessBoard::btn[ROW][COLUMN];


ChessBoard::ChessBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
    // 设置窗体初始化大小
    this->resize(QSize(900, 500));
    initButtonPicture();
    // 双循环创建棋盘
    for(int i = 1; i <= ROW; i++)
    {
        for(int j = 1; j <= COLUMN; j++)
        {
           btn[i-1][j-1]->setGeometry(70 + ((j-1) * 40) + ((i-1) * 20),51 + ((i-1) * 37) ,40 ,50);
           connect(btn[i-1][j-1], SIGNAL(clicked()), this, SLOT(onButtonPictureClick()));
        }
   }
   //创建坐标盘
   for(int i = 0 ; i < ROW; ++i)
   {
       QLabel* numberLabel = new QLabel;
       QLabel* columnLabel = new QLabel;
       columnLabel->setText(QString::number(i));
       numberLabel->setText(QString::number(i));
       numberLabel->setGeometry(80+40*i,30,20,10);
       columnLabel->setGeometry(30+20*i,80+38*i,20,10);
       columnLabel->setParent(this);
       numberLabel->setParent(this);
   }

}

ChessBoard::~ChessBoard()
{
    delete ui;
}

//绘制棋盘边框
void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush bruch(Qt::SolidPattern);
    bruch.setColor(Qt::red);
    int i = 11;
    int j = 0;
    // 循环画下边红色部分的三角形
    while (i--)
    {
        QPolygonF polygon;
        polygon << QPointF(290 + (j * 40), 471) << QPointF(310 + (j * 40), 459) << QPointF(330 + (j * 40), 471);//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);
        j++;
    }
    i = 11;
    j = 0;
    // 循环画上边的红色三角形
    while (i--)
    {
        QPolygonF polygon;
        polygon << QPointF(50 + (j * 40), 51) << QPointF(70 + (j * 40), 63) << QPointF(90 + (j * 40), 51);//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);
        j++;
    }
    // 画一个上边的三分之一长度三角形
    QPolygonF polygon1;
    polygon1 << QPointF(50 + (j * 40), 51) << QPointF(70 + (j * 40), 63) << QPointF(65 + (j * 40), 51);//顺时针取点
    painter.setPen(pen);
    painter.setBrush(bruch);
    painter.drawPolygon(polygon1, Qt::WindingFill);
    // 重新定义一个画刷
    bruch.setColor(Qt::blue);
    int n = 11;
    int m = 0;
    // 循环画左边蓝色三角形
    while (n--)
    {
        QPolygonF polygon;
        polygon << QPointF(50 + (m * 20), 52 + (m * 37)) << QPointF(70 + (m * 20), 89 + (m * 37)) << QPointF(70 + (m * 20), 64 + (m * 37));//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);
        m++;
    }
    // 画左下角三分之一个三角形
    QPolygonF polygon;
    polygon << QPointF(50 + (m * 20), 52 + (m * 37)) << QPointF(56 + (m * 20), 64 + (m * 37)) << QPointF(70 + (m * 20), 64 + (m * 37));//顺时针取点
    painter.setPen(pen);
    painter.setBrush(bruch);
    painter.drawPolygon(polygon, Qt::WindingFill);
    n = 11;
    m = 0;
    // 循环画右边蓝色三角形
    while (n--)
    {
        QPolygonF polygon;
        polygon << QPointF(510 + (m * 20), 63 + (m * 37)) << QPointF(530 + (m * 20), 100 + (m * 37)) << QPointF(510 + (m * 20), 89 + (m * 37));//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);
        m++;
    }
}

//初始化图片为透明（即棋盘为空）
void ChessBoard::initButtonPicture()
{
    for(int i = 0 ; i < ROW; i++)
	{
        for(int j = 0 ; j < COLUMN ; j++)
		{
            btn[i][j] = new QPushButton(this);
            btn[i][j]->setStyleSheet("border-image: url(:/image/000.png);");
        }
    }
}

//按钮点击事件
void ChessBoard::onButtonPictureClick()
{
    // 获取鼠标点击坐标
    // QObject::sender( ) 返回发送信号的对象的指针，返回类型为QObject* 。可使用qobject_cast动态类型转换成对应的发送信息的对象（对象类的基类中需要有QObject）
    //sender()  返回信号来源的对象
    if(Computer::isStart && Computer::isTurn)
	{  // 游戏开始，才进行点击事件的响应
        QPushButton* btn = qobject_cast<QPushButton*>(sender());//获取发射信号的对象，并且向下转型为QPushButton
        if(Computer::onTheOffensiveValue == PLAYER_CHESS)
            btn->setStyleSheet("border-image: url(:/image/111.png);");
        else
            btn->setStyleSheet("border-image: url(:/image/222.png);");
        Computer::isTurn = false;   //设置成不该选手下棋
        btn->setEnabled(false);     //将图片设置为不可点击
        int x = getXByMouse(btn);
        int y = getYByMouse(btn,x);
        Computer::record.push_back(tf.getInputString(x,y));       //存入记录
        Computer::board[x][y] = PLAYER_CHESS;       //设置为人走步
        btn->setText(QString::number(Computer::record.size(),10));        //设置当前棋子为第几颗
        if(jiw.isWin(Computer::board,PLAYER_CHESS)){     //判断下棋是否结束
            QMessageBox::information(this,"win", "player win!!!!", QMessageBox::Ok);
        }
        else{   //电脑下棋
           std::string str= play.playChess();
           int split = str.find(" ");
           int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
           int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
           if(Computer::onTheOffensiveValue == COMPUTER_CHESS)
              this->btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/111.png);");
           else
              this->btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/222.png);");
           Computer::record.push_back(str);
           this->btn[computerX][computerY]->setText(QString::number(Computer::record.size(),10));//设置当前棋子为第几颗
           this->btn[computerX][computerY]->setEnabled(false);
           Computer::board[computerX][computerY] = COMPUTER_CHESS;
           if(jiw.isWin(Computer::board,COMPUTER_CHESS)){     //判断下棋是否结束
               QMessageBox::information(this,"win", "computer win!!!!", QMessageBox::Ok);
           }
           else{
                Computer::isTurn = true;
           }
        }
    }


}

//根据棋盘按钮得到横坐标
int ChessBoard::getXByMouse(QPushButton *btn)
{
    return (btn->pos().y() - 51) / 37;
}

//根据棋盘按钮得到纵坐标
int ChessBoard::getYByMouse(QPushButton *btn,int x)
{
    return ((btn->pos().x() - 70) - (x * 20)) / 40;
}



