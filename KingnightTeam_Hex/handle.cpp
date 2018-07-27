#include "handle.h"
#include "ui_handle.h"

Handle::Handle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Handle)
{
    ui->setupUi(this);
    computerButton = new QRadioButton("computer", this);
    connect(computerButton, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick_Computer()));
    playerButton = new QRadioButton("player",this);
    connect(playerButton, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick_Player()));
    startButton = new QPushButton(this);
    startButton->setText("start");
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startBtnClick()));
    restartButton = new QPushButton(this);
    restartButton->setText("restart");
    connect(restartButton, SIGNAL(clicked(bool)), this, SLOT(restartBtnClick()));
    backButton = new QPushButton(this);
    backButton->setText("back");
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(backBtnClick()));
    chooseFile = new QPushButton(this);
    chooseFile->setText("chooseChessFile");
    connect(chooseFile, SIGNAL(clicked(bool)), this, SLOT(readBtnClick()));
    saveFile = new QPushButton(this);
    saveFile->setText("saveChessFile");
    connect(saveFile, SIGNAL(clicked(bool)), this, SLOT(saveBtnClick()));
    upBtn = new QPushButton(this);
    upBtn->setText("up");
    connect(upBtn, SIGNAL(clicked(bool)), this, SLOT(upBtnClick()));
    downBtn = new QPushButton(this);
    downBtn->setText("down");
    connect(downBtn, SIGNAL(clicked(bool)), this, SLOT(downBtnClick()));
    stepNumberEdit = new QLineEdit(this);
    toBtn = new QPushButton(this);
    toBtn->setText("to");
    connect(toBtn, SIGNAL(clicked(bool)), this, SLOT(toBtnClick()));
    rightLayout = new QGridLayout;
    rightLayout->addWidget(computerButton,0,0);
    rightLayout->addWidget(playerButton,0,1);
    rightLayout->addWidget(startButton,1,0);
    rightLayout->addWidget(restartButton,1,1);
    rightLayout->addWidget(backButton,2,0);
    rightLayout->addWidget(chooseFile,2,1);
    rightLayout->addWidget(saveFile,3,0);
    rightLayout->addWidget(stepNumberEdit,4,0);
    rightLayout->addWidget(toBtn,4,1);
    rightLayout->addWidget(upBtn,5,0);
    rightLayout->addWidget(downBtn,5,1);
    this->setLayout(rightLayout);
}

Handle::~Handle()
{
    delete ui;
}

//点击开始按钮
void Handle::startBtnClick(){
    if(Computer::isChooseFirst){    //设置了先手才能点击开始游戏
        Computer::isStart = true;       //设置游戏开始
        if(Computer::isFirst){  //是否是先手
            string str= play.playChess();
            int split = str.find(" ");
            int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
            int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
            if(Computer::onTheOffensiveValue == COMPUTER_CHESS)  //先手是电脑
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/111.png);");
            else
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/222.png);");
            Computer::board[computerX][computerY] = COMPUTER_CHESS;
            Computer::record.push_back(str);
            ChessBoard::btn[computerX][computerY]->setText(QString::number(Computer::record.size(),10));
            ChessBoard::btn[computerX][computerY]->setEnabled(false);
            Computer::isTurn = true;
        }else{
            Computer::isTurn = true;
        }
    }
    else if(Computer::isImportChess && (!Computer::isTo)){
        int direction = Computer::onTheOffensiveValue;
        for(int i = 0; i < Computer::chessFile.size(); ++i){
            Location location = Computer::chessFile.at(i);
            Computer::record.push_back(tf.getInputString(location.getX(),location.getY()));       //存入记录
            Computer::board[location.getX()][location.getY()] = direction;       //设置为人走步
            if((Computer::onTheOffensiveValue == COMPUTER_CHESS && i%2 == 0)
                    ||(Computer::onTheOffensiveValue == PLAYER_CHESS && i%2 == 1))
               ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/111.png);");
            else
               ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/222.png);");
            ChessBoard::btn[location.getX()][location.getY()]->setText(QString::number(Computer::record.size(),10));        //设置当前棋子为第几颗
            if(direction == COMPUTER_CHESS){
                direction = PLAYER_CHESS;
            }
            else{
                direction = COMPUTER_CHESS;
            }
        }
        Computer::isStart = true;
        Computer::isChooseFirst = true;
        if((Computer::onTheOffensiveValue == COMPUTER_CHESS && Computer::record.size()% 2 == 0)
                ||(Computer::onTheOffensiveValue == PLAYER_CHESS && Computer::record.size()%2 == 1)){
            string str= play.playChess();
            int split = str.find(" ");
            int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
            int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
            if(Computer::onTheOffensiveValue == COMPUTER_CHESS)  //先手是电脑
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/111.png);");
            else
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/222.png);");
            Computer::board[computerX][computerY] = COMPUTER_CHESS;
            Computer::record.push_back(str);
            ChessBoard::btn[computerX][computerY]->setText(QString::number(Computer::record.size(),10));
            ChessBoard::btn[computerX][computerY]->setEnabled(false);
            Computer::isTurn = true;
        }
        else{
             Computer::isTurn = true;
        }
    }
    else if(Computer::isTo){
        Computer::isStart = true;
        Computer::isChooseFirst = true;
        if((Computer::onTheOffensiveValue == COMPUTER_CHESS && Computer::step% 2 == 0)
                ||(Computer::onTheOffensiveValue == PLAYER_CHESS && Computer::step%2 == 1)){
            string str= play.playChess();
            int split = str.find(" ");
            int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
            int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
            if(Computer::onTheOffensiveValue == COMPUTER_CHESS)  //先手是电脑
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/111.png);");
            else
               ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/222.png);");
            Computer::board[computerX][computerY] = COMPUTER_CHESS;
            Computer::record.push_back(str);
            ChessBoard::btn[computerX][computerY]->setText(QString::number(Computer::record.size(),10));
            ChessBoard::btn[computerX][computerY]->setEnabled(false);
            Computer::isTurn = true;
        }
        else{
             Computer::isTurn = true;
        }
    }
    else{
        QMessageBox::information(this,"tip", "Please choose first player!!!!", QMessageBox::Ok);
    }

}

void Handle::restartBtnClick(){
    Computer::isFirst = false;
    Computer::isStart = false;
    Computer::isChooseFirst = false;
    Computer::isTurn = false;
	Computer::uctCount = 0;
    Computer::record.clear();
    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            Computer::board[i][j] = NO_CHESS;
        }
    }

    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            ChessBoard::btn[i][j]->setStyleSheet("border-image: url(:/image/000.png);");
            ChessBoard::btn[i][j]->setEnabled(true);
			ChessBoard::btn[i][j]->setText("");
        }
    }
}

void Handle::backBtnClick(){
    Computer::isTurn = !(Computer::isTurn);
    string lastStr = Computer::record.at(Computer::record.size()-1);
    int split = lastStr.find(" ");
    int computerY = tf.getInt(lastStr.substr(split+1,lastStr.length()-split-1));
    int computerX = tf.getInt(lastStr.substr(0,lastStr.length()-(lastStr.length()-split)));
    ChessBoard::btn[computerX][computerY]->setStyleSheet("border-image: url(:/image/000.png);");
	ChessBoard::btn[computerX][computerY]->setText("");
    ChessBoard::btn[computerX][computerY]->setEnabled(true);
    Computer::record.pop_back();    //移除栈顶元素
	Computer::board[computerX][computerY] = NO_CHESS;
}

//跳转到指定步数
void Handle::toBtnClick(){
    QString str =  stepNumberEdit->text();
    int step = str.toInt();
    Computer::step = step;
    if(Computer::isImportChess){
            Computer::isTo = true;
            int direction = Computer::onTheOffensiveValue;
            for(int i = 0; i < Computer::step; ++i){
                Location location = Computer::chessFile.at(i);
                Computer::record.push_back(tf.getInputString(location.getX(),location.getY()));       //存入记录
                Computer::board[location.getX()][location.getY()] = direction;       //设置为人走步
                if((Computer::onTheOffensiveValue == COMPUTER_CHESS && i % 2 == 0)
                        ||(Computer::onTheOffensiveValue == PLAYER_CHESS && i % 2 == 1))
                   ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/111.png);");
                else
                   ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/222.png);");
                ChessBoard::btn[location.getX()][location.getY()]->setText(QString::number(Computer::record.size(),10));        //设置当前棋子为第几颗
                if(direction == COMPUTER_CHESS){
                    direction = PLAYER_CHESS;
                }
                else{
                    direction = COMPUTER_CHESS;
                }
            }
        }
    else{       //未导入棋盘
        QMessageBox::information(this,"error", "don't import chess board!!!!", QMessageBox::Ok);
    }
}

//前进一步
void Handle::upBtnClick(){
    int direction ;
    if((Computer::onTheOffensiveValue == COMPUTER_CHESS
            && Computer::step %2 == 0)
            ||(Computer::onTheOffensiveValue == PLAYER_CHESS && Computer::step % 2 == 1)){
       direction = COMPUTER_CHESS;
    }
    else{
        direction = PLAYER_CHESS;
    }
    Location location = Computer::chessFile.at(Computer::step);
    Computer::record.push_back(tf.getInputString(location.getX(),location.getY()));       //存入记录
    Computer::board[location.getX()][location.getY()] = direction;       //设置为人走步
    if((Computer::onTheOffensiveValue == COMPUTER_CHESS && Computer::step % 2 == 0)
            ||(Computer::onTheOffensiveValue == PLAYER_CHESS && Computer::step%2 == 1))
       ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/111.png);");
    else
       ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/222.png);");
    ChessBoard::btn[location.getX()][location.getY()]->setText(QString::number(Computer::record.size(),10));  //设置当前棋子为第几颗
    Computer::step += 1;
}

//后退一步
void Handle::downBtnClick(){
    Location location = Computer::chessFile.at(Computer::step-1);
    Computer::record.pop_back();    //删除记录
    ChessBoard::btn[location.getX()][location.getY()]->setStyleSheet("border-image: url(:/image/000.png);");
    ChessBoard::btn[location.getX()][location.getY()]->setText("");  //清除棋子
    Computer::step -= 1;
}

//读取棋谱
void Handle::readBtnClick(){// QDir::currentPath()
    QString filename = QFileDialog::getOpenFileName(
       this,
       "Open Document",
      QDir::currentPath(),
       "Document files (*.txt);;All files(*.*)");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    int count = -1 ;
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        QList<QString> lst;
        lst=str.split(' ');
        QListIterator<QString> i(lst);
        int x,y;
        while (i.hasNext()){
            if(count == -1){
                Computer::onTheOffensiveValue = i.next().toInt();
                count++;
            }
            else{
               if(count % 2 == 0) {
                   x = i.next().toInt();
                   count++;
               }
               else{
                   y = i.next().toInt();
                   Location location(x,y);
                   Computer::chessFile.push_back(location);
                   count++;
               }
            }
        }
    }
    Computer::isImportChess = true;
    Computer::step = Computer::chessFile.size();
}

//保存棋谱
void Handle::saveBtnClick(){
    QString fileName = QFileDialog::getSaveFileName (this,
                            tr("saveChess"),"",tr("(*.txt)"));
                if(!fileName.isEmpty ())
                {
                    QFile file(fileName);
                    if(!file.open (QIODevice::WriteOnly))
                    {
                        QMessageBox msgBox;
                        msgBox.setText("保存文件失败！");
                        msgBox.exec();
                    }
                    else
                    {
                        QString qs = QString::number(Computer::onTheOffensiveValue);
                        qs = qs+"\r\n";
                        for(int i = 0 ; i < Computer::record.size(); ++i){
                              QString q_str = QString::fromStdString(Computer::record.at(i));
                              qs = qs+q_str+"\r\n";
                        }
                        QTextStream stream(&file);
                        stream << qs;
                        stream.flush ();
                        file.close ();
                    }
                }
}



//点击电脑单选按钮
void Handle::radioBtnClick_Computer(){
    Computer::isFirst = true;       //设置是否为先手
    Computer::isChooseFirst = true; //设置选择了先手
    Computer::onTheOffensiveValue = COMPUTER_CHESS; //设置先手棋的表示方式
}


//点击选手单选按钮
void Handle::radioBtnClick_Player(){
    Computer::isFirst = false;      //设置是否为先手
    Computer::isChooseFirst = true; //设置选择了先手
    Computer::onTheOffensiveValue = PLAYER_CHESS;//设置先手棋的表示方式
}

//初始化棋盘
void Handle::initBoard(int board[][COLUMN]){
    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            board[i][j] = NO_CHESS;
        }
    }
}

void Handle::initBoardPicture(QPushButton* btn[][COLUMN]){
    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            btn[i][j]->setStyleSheet("border-image: url(:/image/000.png);");
            btn[i][j]->setEnabled(true);
        }
    }
}
