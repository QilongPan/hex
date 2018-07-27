#include "play.h"
Play::Play()
{

}

//下棋
string Play::playChess(){
	/*std::string isWin = fa.isExistMustWin(Computer::board, PLAYER_CHESS,1);
	std::string isWin_My = fa.isExistMustWin(Computer::board, COMPUTER_CHESS,1);
	std::string isWillWin = fa.isExistWillMustWin(PLAYER_CHESS);
	std::string isWillWin_My = fa.isExistWillMustWin(COMPUTER_CHESS);
	if (isWin_My.compare("") != 0){	//己方存在必赢
		return isWin_My;
	}
	if (isWin.compare("") != 0){	//对手存在必赢
		return isWin;
	}
	if (isWillWin_My.compare("success") == 0)		//己方存在必赢局面
	{
		return ps.playChessWhenExistMustWillWin(COMPUTER_CHESS);
	}
	if (isWillWin.compare("success") == 0){	//敌方存在必赢局面
		return ps.playChessWhenExistMustWillWin(PLAYER_CHESS);
	}
	if (isWillWin_My.compare("") != 0 && isWillWin_My.compare("success") != 0){	//己方即将要赢
		return isWillWin_My;
	}
	if (isWillWin.compare("") != 0 && isWillWin.compare("success") != 0){//对手存在即将要赢局面
		return isWillWin;
	}
	//达到启动条件采用uct算法
	if (Computer::record.size() >= 60){
		us = UctSearch(Computer::board);
		move = us.search();
		return tf.getInputString(move.x, move.y);
	} //如果棋小于30颗采用，alpha-beta搜索+经验算法
	else{ //开局库的调用//经验
		string str = ps.playChess();
		if (str.compare("") == 0)
		{
			us = UctSearch(Computer::board);
			move = us.search();
			return tf.getInputString(move.x, move.y);
		}
		else{
			return str;
		}
	}
	return ps.playChessExperience();*/
	std::string isWin = fa.isExistMustWin(Computer::board, PLAYER_CHESS, 1);	//添加一颗whoPlayer方棋则赢
	std::string isWin_My = fa.isExistMustWin(Computer::board, COMPUTER_CHESS, 1);
	std::string isWillWin = fa.isExistWillMustWin(PLAYER_CHESS);	//添加一颗whoPlayer方棋则形成必赢局面
	std::string isWillWin_My = fa.isExistWillMustWin(COMPUTER_CHESS);
	//用于测试uct
	/*
	if (Computer::record.size() >= 0){
		Computer::uctCount++;
		us = UctSearch(Computer::board);
		move = us.search();
		std::cout << move.x << "     " << move.y << "  " << std::endl;
		std::string moveStr = tf.getInputString(move.x, move.y);
		std::cout << moveStr;
		return moveStr;
	}
	*/

	//用于Alpha-Beta算法测试
	/*
	if (Computer::record.size() >= 0){
		abs = AlphaBetaSearch(Computer::board);
		abs.search_AlphaBeta(ALPHABETASEARCHDEPTH, -20000, 20000);
		return tf.getInputString(abs.move.getLocation().getX(), abs.move.getLocation().getY());
	}
	*/

	if (isWin_My.compare("") != 0){	//己方存在必赢
		return isWin_My;
	}

	if (isWin.compare("") != 0){	//对手存在必赢
		return isWin;
	}

	if (isWillWin_My.compare("success") == 0)		//己方存在必赢局面
	{
		return ps.playChessWhenExistMustWillWin(COMPUTER_CHESS);
	}

	if (isWillWin.compare("success") == 0)//敌方存在必赢局面
	{
		return ps.playChessWhenExistMustWillWin(PLAYER_CHESS);
	}

	if (isWillWin_My.compare("") != 0 && isWillWin_My.compare("success") != 0)//己方即将要赢
	{
		return isWillWin_My;
	}

	if (isWillWin.compare("") != 0 && isWillWin.compare("success") != 0)//对手存在即将要赢局面
	{
		return isWillWin;
	}
	//int computerLength = fa.getMaxLength(Computer::board, COMPUTER_CHESS);
	int computerLength = fa.getMaxLengthAddChess(Computer::board, COMPUTER_CHESS);
	int playerLength = fa.getMaxLength(Computer::board, PLAYER_CHESS);
	//达到启动条件采用uct算法
	if (Computer::record.size() >= 6 && computerLength < playerLength){
		Computer::uctCount++;
		us = UctSearch(Computer::board);
		move = us.search();
		return tf.getInputString(move.x, move.y);
	}
	else{ //开局库的调用//经验
		string str = ps.playChess();
		if (str.compare("") == 0)
		{
			us = UctSearch(Computer::board);
			move = us.search();
			return tf.getInputString(move.x, move.y);
		}
		else{
			return str;
		}
	}
	
}

