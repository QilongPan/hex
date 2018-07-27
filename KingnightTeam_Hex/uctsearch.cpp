#include "uctsearch.h"


UctSearch::UctSearch()
{
    nowPlayer = COMPUTER_CHESS;     //设置电脑为先手
    chessNum = Computer::record.size();//更新棋子数目
}

UctSearch::UctSearch(int bo[ROW][COLUMN]){
    for(int i = 0 ; i < ROW; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            board[i][j] = bo[i][j];
        }
    }
    nowPlayer = COMPUTER_CHESS;     //设置先手
    chessNum = Computer::record.size(); //更新棋子数目
}

//UCT启动方法,供外部调用.
UCTMove UctSearch::search()
{
   winCount = 0;   //赢得次数
   drawCount = 0;  //平局
   UCTNode *root = new UCTNode(); //初始化根节点
   UCTMove result;
   int nsimulations = 0;//这是当前模拟次数
   int MaxSimulations = 10000;//这是模拟次数
   vnowPlayer = nowPlayer;
   //可以固定模拟时间,此处选择固定模拟次数
/*   while (nsimulations < MaxSimulations)
   {
       PlaySimulation(root);
       ++nsimulations;
   }*/
   time_t startTime = clock();
   time_t endTime = clock();
   /* while (nsimulations < MaxSimulations)
   {
   PlaySimulation(root);
   ++nsimulations;
   }*/
   while ((endTime - startTime) < 30000)
   {
	   PlaySimulation(root);
	   nsimulations++;
	   endTime = clock();
   }
   //选取根节点最优着法
   result = root->bestMove;
   std::cout <<"times"<< nsimulations << std::endl;
   return result;
}

//1次UCT模拟,核心过程
void UctSearch::PlaySimulation(UCTNode *root)
{
    UCTNode* next;
    int result = checkWinMust(board);
    //若出现结果或平局,则提前结束
    if( result != NORESULT)
    {
	//	std::cout << "result"<<result << std::endl;
        randomresult = result;
        if(randomresult == DRAW)
            drawCount++;
        else if(randomresult == COMPUTER_WIN)
            winCount++;
    }
    //否则,若该节点首次访问,开始随机下棋
    else if(root->visit == 0)
    {
	//	std::cout << "root visit 0" << std::endl;
        randomresult = PlayRandomGame(root);
        if(randomresult == DRAW)
            drawCount++;
        else if(randomresult == COMPUTER_WIN)
            winCount++;
    }
    //若不是首次访问,则根据UCT值选择较优的节点继续进行模拟
    else
    {
	//	std::cout <<"root size1"<< root->child.size()<<std::endl;
		if (root->child.empty()){
			CreateChildren(root);
	//		std::cout << "root size2" << root->child.size() << std::endl;
		}
         next = UCTSelect(root);
         if(next == NULL)
         {
			 std::cout << "null" << std::endl;
         }
         makeMove(next->move);
         PlaySimulation(next);
         unmakeMove(next->move);
    }

    ++root->visit;//更新模拟次数
    UpdateWin(root,randomresult);//根据结果是否更新胜局次数
    if(!root->child.empty())//更新完后,若该根节点孩子不为空,更新最优着法
    {
	//	std::cout << "enter if" << std::endl;
        SetBest(root);
    }
}

//检查是否棋局是否结束
int UctSearch::checkWin(int board[][COLUMN])
{
    if(isWin(board,COMPUTER_CHESS)){     //电脑赢了
        return COMPUTER_WIN;
    }
    else if(isWin(board,PLAYER_CHESS)){      //电脑输了
        return PLAYER_WIN;
    }
    else if(chessNum == ALLCHESSNUMBER){        //平局
        return DRAW;
    }
    else{
        return NORESULT;           //没有输赢
    }

}

int UctSearch::checkWinMust(int board[][COLUMN])
{
	if (isWinMust(board, COMPUTER_CHESS)){     //电脑赢了
		return COMPUTER_WIN;
	}
	else if (isWinMust(board, PLAYER_CHESS)){      //电脑输了
		return PLAYER_WIN;
	}
	else if (chessNum == ALLCHESSNUMBER){        //平局
		return DRAW;
	}
	else{
		return NORESULT;           //没有输赢
	}

}


//双方随机下棋直到终局,返回胜方
int UctSearch::PlayRandomGame(UCTNode *root)
{
	int result = DRAW;
	if ((result = checkWin(board)) != NORESULT)
		return result;
	srand((unsigned)time(NULL));
	int player = vnowPlayer;
	int v_chessNum = 0; //当前棋子数目
	int v_board[ROW][COLUMN] = { 0 };
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			v_board[i][j] = board[i][j];
			if (v_board[i][j] != NO_CHESS)
				v_chessNum++;
		}
	}
	//当未下满棋盘时继续随机下棋
	while (v_chessNum < ALLCHESSNUMBER)
	{
		setVchess(player, v_chessNum, v_board);
		if ((result = checkWin(v_board)) != NORESULT)//每下一步检查是否出现胜负
			return result;
		player = (player % 2) + 1;//交换下棋方
		setVchess(player, v_chessNum, v_board);
		if ((result = checkWin(v_board)) != NORESULT)//同上
			return result;
		player = (player % 2) + 1;  //增加
	}
	return result;
}
/*
int UctSearch::PlayRandomGame(UCTNode *root)
{
	int result = checkWin(board);
	vector<UCTNode> nodes;
	if (result != NORESULT)
		return result;
	srand((unsigned)time(NULL));
	int player = vnowPlayer;
	int v_chessNum = 0; //当前棋子数目
	int v_board[ROW][COLUMN];
	//初始化棋盘
	for (int i = 0; i < ROW; ++i){
		for (int j = 0; j < COLUMN; ++j){
			v_board[i][j] = 0;
		}
	}
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			v_board[i][j] = board[i][j];
			if (v_board[i][j] != NO_CHESS){
				v_chessNum++;
			}
			else{
				UCTNode node;
				node.move.x = i;
				node.move.y = j;
				nodes.push_back(node);
			}
		}
	}
	//当未下满棋盘时继续随机下棋
	while (true)
	{
		result = checkWin(v_board);
		if (result != NORESULT)//同上
			return result;
		int index = rand() % nodes.size();
		v_board[nodes.at(index).move.x][nodes.at(index).move.y] = player;
		++v_chessNum;
		result = checkWin(v_board);
		if (result != NORESULT)//每下一步检查是否出现胜负
			return result;
		player = (player % 2) + 1;//交换下棋方
		nodes.erase(nodes.begin() + index);

		index = rand() % nodes.size();
		v_board[nodes.at(index).move.x][nodes.at(index).move.y] = player;
		++v_chessNum;
		result = checkWin(v_board);
		if (result != NORESULT)//同上
			return result;
		player = (player % 2) + 1;  //增加
		nodes.erase(nodes.begin() + index);
	}
	return DRAW;
}
*/
//UCT最优节点选择.公式UCT = UCTK * sqrt(log(root->visit) / (5 * next->visit))
//该公式与访问节点的频数与淘汰劣质节点有关(分子分母决定),性质未详细证明.
UCTNode* UctSearch::UCTSelect(UCTNode *root)
{
    double UCT = 0;
    double winrate = 0;
    double bestUct = 0;
    double UCTvalue ;
    UCTNode *result = NULL;
    srand((unsigned)time(NULL));
    for(int i = 0; i < root->child.size(); ++i)
    {
        UCTNode *next = &root->child[i];
        //此处优化.分成两棵树?双方各一棵UCT,访问节点数不互相影响
        if(next->visit > 0)
        {
            winrate = next->win * 1.0 / next->visit;
            //	return (该走步赢的次数 / 该走步模拟次数) + 常数 * sqrt(2 * log(模拟总次数)/该走步模拟次数);
            //   return (uctNdoe.CURRENT_WIN / uctNdoe.CURRENT_TIMES) + uctNdoe.c * sqrt(2 * log(PARENT_TIMES) / uctNdoe.CURRENT_TIMES);
     //       UCT = UCTK * sqrt(log(root->visit) / (5 * next->visit));
			UCT = UCTK * sqrt(log(root->visit)/(8*next->visit));
            if(vnowPlayer == COMPUTER_CHESS)
                UCTvalue = winrate + UCT;
            else
                UCTvalue = 1 - winrate + UCT;
        }
        else
        {
            UCTvalue = 10000 + rand() % 1000; //初次访问给予最大UCT值,让其有机会被访问到
        }
        if(UCTvalue > bestUct)//选择最优UCT值
        {
            bestUct = UCTvalue;
            result = next;//得到更优节点
        }
    }
    return result;//最终返回最优节点
}

//往虚拟棋盘随机下棋
void UctSearch::setVchess(int player,int &v_chessNum,int v_board[][COLUMN])
{
    if( v_chessNum == 121 ) return;
    int x = rand() % 11;
    int y = rand() % 11;
    while(v_board[x][y] != NO_CHESS )
    {
        x = rand() % 11;
        y = rand() % 11;
    }
    v_board[x][y] = player;
    ++v_chessNum;
}

//生成符合规则的子节点
void UctSearch::CreateChildren(UCTNode *root)
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			if (board[i][j] == NO_CHESS)
			{
				UCTNode child;
				child.move.x = i;
				child.move.y = j;
				root->child.push_back(child);
			}
		}
	}

	/*
	vector<Location> locations;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			if (board[i][j] != NO_CHESS)
			{
				ps.getLocationsByRecursionByBoard(locations, i, j, 1, 100, board);
			}
		}
	}
	for (int m = 0; m < locations.size(); ++m)
	{
		UCTNode child;
		child.move.x = locations.at(m).getX();
		child.move.y = locations.at(m).getY();
		root->child.push_back(child);
	}
	*/
	
}

//下子
void UctSearch::makeMove(UCTMove move)
{

    board[move.x][move.y] = vnowPlayer;
    vnowPlayer = (vnowPlayer%2)+1;      //更换下棋方
    ++chessNum;
}

//下子恢复
void UctSearch::unmakeMove(UCTMove move)
{
    board[move.x][move.y] = NO_CHESS;
    vnowPlayer = (vnowPlayer%2)+1;      //更换下棋方
    --chessNum;
}

//更新根节点胜率
void UctSearch:: UpdateWin(UCTNode *root, int result)
{
    if(result == COMPUTER_WIN)
    {
        root->win++;
    }

}

//设置根节点最优走步
void UctSearch::SetBest(UCTNode *root)
{
//	std::cout << "setBest" << root->child.size() << std::endl;
    double bestValue = -1;
    for(int i = 0; i < root->child.size(); ++i)
    {
        UCTNode *next = &root->child[i];
        double winrate = next->win * 1.0 / next->visit;
        if(winrate > bestValue)
        {
            bestValue = winrate;
            root->bestMove.x = next->move.x;
            root->bestMove.y = next->move.y;
        }
    }
}

//判断电脑或选手是否赢棋
bool UctSearch::isWin(int board[][COLUMN], int whoPlayer){
   /* if (whoPlayer == Computer::onTheOffensiveValue){	//是先手，则为红方
        Board<int> tempBoard(board);
        redDFS searcher(&tempBoard, whoPlayer);
        return searcher.solve();
    }
    else{
        Board<int> tempBoard(board);
        blueDFS searcher(&tempBoard,whoPlayer );
        return searcher.solve();	//蓝方
    }*/
	return jiw.isWillMustWin(board, whoPlayer);
}

//判断电脑或选手是否赢棋
bool UctSearch::isWinMust(int board[][COLUMN], int whoPlayer){
	if (whoPlayer == Computer::onTheOffensiveValue){	//是先手，则为红方
		Board<int> tempBoard(board);
		redDFS searcher(&tempBoard, whoPlayer);
		return searcher.solve();
	}
	else{
		Board<int> tempBoard(board);
		blueDFS searcher(&tempBoard,whoPlayer );
		return searcher.solve();	//蓝方
	}
//	return jiw.isWillMustWin(board, whoPlayer);
}
