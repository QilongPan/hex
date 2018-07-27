#include "playchess_start.h"

PlayChess_Start::PlayChess_Start()
{

}

//初始化开局库
void PlayChess_Start::initStartVector()
{
    if(Computer::onTheOffensiveValue == COMPUTER_CHESS)
	{        
        int startX = 0;
        int startY = 5;
        for(int i = 5 ; i < 11 ; i++)
		{
            std::vector<std::string> temVec;
            temVec.push_back(tf.getInputString(startX,startY));
            temVec.push_back(tf.getInputString(startX+2,startY-1));
            temVec.push_back(tf.getInputString(startX+4,startY-2));
            temVec.push_back(tf.getInputString(startX+6,startY-3));
            temVec.push_back(tf.getInputString(startX+8,startY-4));
            temVec.push_back(tf.getInputString(startX+10,startY-5));
            startVector.push_back(temVec);
            startX = 0;
            startY = startY+1;
        }
    }
    else
	{   
        int startX = 5 ;
        int startY = 0 ;
        for(int i = 5 ; i < 11 ; i++)
		{
            std::vector<std::string> temVec;
            temVec.push_back(tf.getInputString(startX,startY));
            temVec.push_back(tf.getInputString(startX-1,startY+2));
            temVec.push_back(tf.getInputString(startX-2,startY+4));
            temVec.push_back(tf.getInputString(startX-3,startY+6));
            temVec.push_back(tf.getInputString(startX-4,startY+8));
            temVec.push_back(tf.getInputString(startX-5,startY+10));
            startVector.push_back(temVec);
            startX = startX+1;
            startY = 0;
        }
    }
}

string PlayChess_Start::playChess()
{
   /* initStartVector();   
    if(Computer::onTheOffensiveValue == COMPUTER_CHESS)
	{
        return playChess_IsFirst();
    }
    else
	{
        return playChess_IsNotFirst();
    }*/
	if (Computer::record.size() == 0)
	{
		/*std::vector<std::string> startIndexs;
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				startIndexs.push_back(tf.getInputString(i, j));
			}
		}
		srand((unsigned)time(NULL));
		int startBoardIndex = rand() % startIndexs.size();       //产生0到4的随机数，用于选取开局库
		return startIndexs.at(startBoardIndex);*/
		std::vector<std::string> startIndexs;
		if (Computer::onTheOffensiveValue == COMPUTER_CHESS)
		{
			startIndexs.push_back(tf.getInputString(5, 3));
			startIndexs.push_back(tf.getInputString(5, 4));
			startIndexs.push_back(tf.getInputString(7, 2));
			startIndexs.push_back(tf.getInputString(7, 3));
		}
		else{
			startIndexs.push_back(tf.getInputString(3, 5));
			startIndexs.push_back(tf.getInputString(4, 3));
			startIndexs.push_back(tf.getInputString(5, 3));
			startIndexs.push_back(tf.getInputString(4, 5));
		}
		srand((unsigned)time(NULL));
		int startBoardIndex = rand() % startIndexs.size();       //产生0到4的随机数，用于选取开局库
		return startIndexs.at(startBoardIndex);
	}
	else
	{
		return playChessExperience();
	}
}

string PlayChess_Start::playChess_IsFirst(){
    if(Computer::record.size() == 0){       //如果是第一颗棋,从开局库中选取一颗棋来进行走步
        srand((unsigned)time(NULL));
        int startBoardIndex = rand() % 5;       //产生0到4的随机数，用于选取开局库
        std::vector<std::string> startBoard = startVector.at(startBoardIndex);
        int startChessIndex = rand()% 6;       //产生0到5的随机数，用于选取开局库中的某一走步
        std::string moveStr = startBoard.at(startChessIndex);
        Computer::startBoardRecord.push_back(moveStr);      //记录走步
        Computer::startBoard = startBoard;
        return moveStr;
    }
    else{       //不是第一颗棋
        //如果自己开局库局面的棋位置被占据
        if(Computer::isSuccess){
            string isDu = getWhichIsWalled();
            if(isDu.compare("false") == 0){  //开局库形成失败
                Computer::isSuccess = false;
				return playChessExperience();
            }
            else if(isDu.compare("") != 0){     //如果被堵了左下和下
                return isDu;
            }
            else{       //开局库没有被堵
                if(Computer::startBoardRecord.size()>= 6){       //存在开局库局面生成成功
                    return playChessStartSuccess();
                }
                vector<string> startBoard = Computer::startBoard;
                string str="";
                for(int i = 0;i < 6; i++){
                    str = startBoard.at(i);
                    int split = str.find(" ");
                    int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
                    int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
                    if(Computer::board[computerX][computerY] == NO_CHESS
                            && Computer::startBoardRecord.size()<= 5){
                        Computer::startBoardRecord.push_back(str);
                        return str;
                    }
                }
                return str;
            }
        }
        else{
	          return playChessExperience();
        }
    }
}
//判断开局库被堵情况
string PlayChess_Start::getWhichIsWalled(){
    vector<string> records = Computer::record;
    vector<string> startBoard = Computer::startBoard;
    string str = records.at(records.size()-1);      //上一步记录
    int split = str.find(" ");
    int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
    int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
    for(int i = 0 ; i < startBoard.size() ; i++){
        string start = startBoard.at(i);
        int splitStart = start.find(" ");
        int y = tf.getInt(start.substr(splitStart+1,start.length()-splitStart-1));
        int x = tf.getInt(start.substr(0,start.length()-(start.length()-splitStart)));
        if(((x+1) == computerX)&&((y-1) == computerY)){ //左下被堵
            if(cm.isValid(x+1,y)){
                return tf.getInputString(x+1,y);
            }
        }
        else if(((x+1) == computerX)&&(y == computerY)){//下被堵
            if(cm.isValid(x+1,y-1)){
                 return tf.getInputString(x+1,y-1);
            }
        }
        else if(((x+2) == computerX) && ((y-1) == computerY)){  //如果开局库形成失败
            return "false";
        }
    }
    return "";      //没有被堵
}

string PlayChess_Start::getWhichIsWalled_LeftToRight()
{
    vector<string> records = Computer::record;
    vector<string> startBoard = Computer::startBoard;
    string str = records.at(records.size()-1);      //上一步记录
    int split = str.find(" ");
    int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
    int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
    for(int i = 0 ; i < startBoard.size() ; i++){
        string start = startBoard.at(i);
        int splitStart = start.find(" ");
        int y = tf.getInt(start.substr(splitStart+1,start.length()-splitStart-1));
        int x = tf.getInt(start.substr(0,start.length()-(start.length()-splitStart)));
        if(((x-1) == computerX)&&((y+1) == computerY)){ //右上被堵
            if(cm.isValid(x,y+1)){
                return tf.getInputString(x,y+1);
            }
        }
        else if((x == computerX)&&((y+1) == computerY)){//下被堵
            if(cm.isValid(x-1,y+1)){
                 return tf.getInputString(x-1,y+1);
            }
        }
        else if(((x-1) == computerX) && ((y+2) == computerY)){  //如果开局库形成失败
            return "false";
        }
    }
    return "";      //没有被堵
}


string PlayChess_Start::playChess_IsNotFirst(){
    string isWin = fa.isExistMustWin(Computer::board,PLAYER_CHESS,1);
    string isWin_My = fa.isExistMustWin(Computer::board,COMPUTER_CHESS,1);
    if(isWin.compare("") == 0){     //不存在必赢
        if(Computer::record.size() == 1){       //如果是第一颗棋,从开局库中选取一颗棋来进行走步
            srand((unsigned)time(NULL));
            int startBoardIndex = rand() % 5;       //产生0到4的随机数，用于选取开局库
            vector<string> startBoard = startVector.at(startBoardIndex);
            int startChessIndex = rand()% 6;       //产生0到5的随机数，用于选取开局库中的某一走步
            string moveStr = startBoard.at(startChessIndex);
            Computer::startBoardRecord.push_back(moveStr);      //记录走步
            Computer::startBoard = startBoard;
            return moveStr;
        }
        else{       //已经开局
            //如果自己开局库局面的棋位置被占据
            if(Computer::isSuccess){
                string isDu = getWhichIsWalled_LeftToRight();
                if(isDu.compare("false") == 0){  //开局库形成失败,采用alpha-beta算法
                    Computer::isSuccess = false;
                    string str = Computer::record.at(Computer::record.size()-1);
					return playChessExperience();
                }
                else if(isDu.compare("") != 0){     //如果被堵了左下和下
                    return isDu;
                }
                else{       //开局库没有被堵
                    if(Computer::startBoardRecord.size()>= 6){       //存在开局库局面生成成功
                        return playChessStartSuccess_LeftToRight();
                    }
                    vector<string> startBoard = Computer::startBoard;
                    string str="";
                    for(int i = 0;i < 6; i++){
                        str = startBoard.at(i);
                        int split = str.find(" ");
                        int computerY = tf.getInt(str.substr(split+1,str.length()-split-1));
                        int computerX = tf.getInt(str.substr(0,str.length()-(str.length()-split)));
                        if(Computer::board[computerX][computerY] == NO_CHESS
                                && Computer::startBoardRecord.size()<= 5){
                            Computer::startBoardRecord.push_back(str);
                            return str;
                        }
                    }
                    return str;
                }
            }
            else{
				return playChessExperience();
            }
        }
    }
    else{
        if(isWin_My.compare("") != 0){
            return isWin_My;
        }
        return isWin;
    }

}






string PlayChess_Start::playChessStartSuccess(){
    vector<string> startBoard = Computer::startBoard;
    for(int i = 0 ; i < startBoard.size() ; i++){
        string start = startBoard.at(i);
        int splitStart = start.find(" ");
        int y = tf.getInt(start.substr(splitStart+1,start.length()-splitStart-1));
        int x = tf.getInt(start.substr(0,start.length()-(start.length()-splitStart)));
        if(Computer::board[x+1][y-1] == COMPUTER_CHESS
                || Computer::board[x+1][y] == COMPUTER_CHESS){

        }
        else{
            if(Computer::board[x+1][y-1] == NO_CHESS){
                return tf.getInputString(x+1,y-1);
            }
            else if(Computer::board[x+1][y] == NO_CHESS){
                return tf.getInputString(x+1,y);
            }
        }
    }
    return "";
}

string PlayChess_Start::playChessStartSuccess_LeftToRight(){
    vector<string> startBoard = Computer::startBoard;
    for(int i = 0 ; i < startBoard.size() ; i++){
        string start = startBoard.at(i);
        int splitStart = start.find(" ");
        int y = tf.getInt(start.substr(splitStart+1,start.length()-splitStart-1));
        int x = tf.getInt(start.substr(0,start.length()-(start.length()-splitStart)));
        if(Computer::board[x-1][y+1] == COMPUTER_CHESS
                || Computer::board[x][y+1] == COMPUTER_CHESS){

        }
        else{
            if(Computer::board[x-1][y+1] == NO_CHESS){
                return tf.getInputString(x-1,y+1);
            }
            else if(Computer::board[x][y+1] == NO_CHESS){
                return tf.getInputString(x,y+1);
            }
        }
    }
    return "";
}

std::string PlayChess_Start::playChessWhenExistMustWillWin(int whoPlayer)
{
	std::vector<Location> locations = fa.getEmptyChessOnBoard(Computer::board);
	Location location = locations.at(0);
	fa.makeMove(Move(locations.at(0), whoPlayer), Computer::board);
	int length = fa.getMaxLength_Actual(Computer::board, whoPlayer);
	fa.unMakeMove(Move(locations.at(0), whoPlayer), Computer::board);
	for (int i = 1; i < locations.size(); i++)
	{
		fa.makeMove(Move(locations.at(i), whoPlayer), Computer::board);
		int currentMaxLength = fa.getMaxLength_Actual(Computer::board, whoPlayer);
		if (currentMaxLength > length && fa.isExistWillMustWin(whoPlayer).compare("success") == 0){
			location = locations.at(i);
			length = currentMaxLength;
		}
		fa.unMakeMove(Move(locations.at(i), whoPlayer), Computer::board);
	}
	return tf.getInputString(location.getX(), location.getY());
	/*std::vector<Location> locations = fa.getEmptyChessOnBoard(Computer::board);
	std::vector<std::vector<Location>> locationsVec;
	std::vector<Location> arr;
	fa.computeAllChoices(locations, locations.size(), locationsVec, 0, 2, arr, 0);		//得到所有组合
	fa.makeMoves(locationsVec.at(0), Computer::board, whoPlayer);
	int maxLength = fa.getMaxLength_Actual(Computer::board, whoPlayer);
	fa.unMakeMoves(locationsVec.at(0), Computer::board);
	std::vector<Location> location = locationsVec.at(0);
	for (int i = 1; i < locationsVec.size(); i++)
	{
		fa.makeMoves(locationsVec.at(i), Computer::board,whoPlayer);
		int currentMaxLength = fa.getMaxLength_Actual(Computer::board, whoPlayer);
		if (currentMaxLength > maxLength){
			location = locationsVec.at(i);
			maxLength = currentMaxLength;
		}
		fa.unMakeMoves(locationsVec.at(i), Computer::board);
	}
	return tf.getInputString(location.at(0).getX(), location.at(0).getY());*/
}

string PlayChess_Start::playChessExperience()
{
/*	string isCutOffMy = isExistTruncationIndex(Computer::board, COMPUTER_CHESS);	//存在被截断
	if (isCutOffMy.compare("") != 0 && Computer::record.size() > 8)
	{
		return isCutOffMy;
	}*/

	//得到判断的坐标
	vector<Location> locations = getLocations(FINDDEPTH, FINDNUMBER);
	vector<Location> laterLocations;
	for (int i = 0; i < locations.size(); i++)
	{
		locations.at(i).setScore(0);
	}
	for (int i = 0; i < locations.size(); i++)
	{
		laterLocations.push_back(locations.at(i));
	}
	Location location = fa.getBestLocation(locations, COMPUTER_CHESS);
	Location laterLocation = fa.getBestLocation(laterLocations, PLAYER_CHESS);
	if (location.getX() == NULL)
	{
		return "";
	}
	if (location.getScore() >= laterLocation.getScore())
	{
		return tf.getInputString(location.getX(), location.getY());
	}
	else
	{
		return tf.getInputString(laterLocation.getX(), laterLocation.getY());
	}
}

//得到周围的点
vector<Location> PlayChess_Start::getLocations(int depth, int count)
{
	vector<Location> locations;
	int recordSize = Computer::record.size();
	vector<string> records = Computer::record;
	for (int i = recordSize - 1; i >= 0; --i)
	{
		string lastStr = records.at(i);
		int split = lastStr.find(" ");
		int computerY = tf.getInt(lastStr.substr(split + 1, lastStr.length() - split - 1));
		int computerX = tf.getInt(lastStr.substr(0, lastStr.length() - (lastStr.length() - split)));
		getLocationsByRecursion(locations, computerX, computerY, FINDDEPTH);
		if (locations.size() >= FINDNUMBER)
		{
			break;
		}
	}
	vector<Location> returnLocations;
	returnLocations.push_back(locations.at(0));
	for (int i = 0; i < locations.size(); i++){
		bool flag = true;
		for (int j = 0; j < returnLocations.size(); j++){
			if (returnLocations.at(j) == locations.at(i)){
				flag = false;
				break;
			}
		}
		if (flag){
			returnLocations.push_back(locations.at(i));
		}
	}
	return returnLocations;
}

std::vector<Location> PlayChess_Start::getLocationsByIndex(int depth,int count, int x, int y, const int board[][COLUMN])
{
	vector<Location> locations;
	getLocationsByRecursionByBoard(locations, x, y, depth,count,board);
	vector<Location> returnLocations;
	if (returnLocations.size() <= 0)
	{
		return returnLocations;
	}
	else{
		returnLocations.push_back(locations.at(0));
		for (int i = 0; i < locations.size(); i++){
			bool flag = true;
			for (int j = 0; j < returnLocations.size(); j++){
				if (returnLocations.at(j) == locations.at(i)){
					flag = false;
					break;
				}
			}
			if (flag){
				returnLocations.push_back(locations.at(i));
			}
		}
		return returnLocations;
	}
	
}

/*void PlayChess_Start::getLocationsByRecursionByBoard(vector<Location> &locations, int computerX, int computerY, int depth,int count, const int board[][COLUMN])
{
	if (depth <= 0||locations.size() >= count)
	{
		return;
	}
	if (cm.isValid(computerX, computerY + 1) && board[computerX][computerY + 1] == NO_CHESS)
	{
		Location location(computerX, computerY + 1);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX, computerY + 1, depth - 1,count,board);
	}
	if (cm.isValid(computerX + 1, computerY) && board[computerX + 1][computerY] == NO_CHESS)
	{
		Location location(computerX + 1, computerY);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX + 1, computerY, depth - 1, count, board);
	}
	if (cm.isValid(computerX, computerY - 1) && board[computerX][computerY - 1] == NO_CHESS)
	{
		Location location(computerX, computerY - 1);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX, computerY - 1, depth - 1, count, board);
	}
	if (cm.isValid(computerX - 1, computerY) && board[computerX - 1][computerY] == NO_CHESS)
	{
		Location location(computerX - 1, computerY);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX - 1, computerY, depth - 1, count, board);
	}
	if (cm.isValid(computerX - 1, computerY + 1) && board[computerX - 1][computerY + 1] == NO_CHESS)
	{
		Location location(computerX - 1, computerY + 1);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX - 1, computerY + 1, depth - 1, count, board);
	}
	if (cm.isValid(computerX + 1, computerY - 1) && board[computerX + 1][computerY - 1] == NO_CHESS)
	{
		Location location(computerX + 1, computerY - 1);
		locations.push_back(location);
		getLocationsByRecursionByBoard(locations, computerX + 1, computerY - 1, depth - 1, count, board);
	}
}*/
void PlayChess_Start::getLocationsByRecursionByBoard(vector<Location> &locations, int computerX, int computerY, int depth, int count, const int board[][COLUMN])
{
	if (depth <= 0 || locations.size() >= count)
	{
		return;
	}
	if (cm.isValid(computerX, computerY + 1) && board[computerX][computerY + 1] == NO_CHESS)
	{
		Location location(computerX, computerY + 1);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX, computerY + 1, depth - 1, count, board);
		}

	}
	if (cm.isValid(computerX + 1, computerY) && board[computerX + 1][computerY] == NO_CHESS)
	{
		Location location(computerX + 1, computerY);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX + 1, computerY, depth - 1, count, board);
		}
	}
	if (cm.isValid(computerX, computerY - 1) && board[computerX][computerY - 1] == NO_CHESS)
	{
		Location location(computerX, computerY - 1);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX, computerY - 1, depth - 1, count, board);
		}
	}
	if (cm.isValid(computerX - 1, computerY) && board[computerX - 1][computerY] == NO_CHESS)
	{
		Location location(computerX - 1, computerY);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX - 1, computerY, depth - 1, count, board);
		}
	}
	if (cm.isValid(computerX - 1, computerY + 1) && board[computerX - 1][computerY + 1] == NO_CHESS)
	{
		Location location(computerX - 1, computerY + 1);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX - 1, computerY + 1, depth - 1, count, board);
		}
	}
	if (cm.isValid(computerX + 1, computerY - 1) && board[computerX + 1][computerY - 1] == NO_CHESS)
	{
		Location location(computerX + 1, computerY - 1);
		vector<Location>::iterator it = find(locations.begin(), locations.end(), location);
		if (it == locations.end())
		{
			locations.push_back(location);
			getLocationsByRecursionByBoard(locations, computerX + 1, computerY - 1, depth - 1, count, board);
		}
	}
}
/*
传入位置和搜索深度，得到向外扩展的位置
*/
void PlayChess_Start::getLocationsByRecursion(vector<Location> &locations, int computerX, int computerY, int depth)
{
	if (depth <= 0 || locations.size() >= FINDNUMBER)
	{
		return;
	}
	if (cm.isValid(computerX, computerY + 1) && Computer::board[computerX][computerY + 1] == NO_CHESS)
	{
		Location location(computerX, computerY + 1);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX, computerY + 1, depth - 1);
	}
	if (cm.isValid(computerX + 1, computerY) && Computer::board[computerX + 1][computerY] == NO_CHESS)
	{
		Location location(computerX + 1, computerY);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX + 1, computerY, depth - 1);
	}
	if (cm.isValid(computerX, computerY - 1) && Computer::board[computerX][computerY - 1] == NO_CHESS)
	{
		Location location(computerX, computerY - 1);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX, computerY - 1, depth - 1);
	}
	if (cm.isValid(computerX - 1, computerY) && Computer::board[computerX - 1][computerY] == NO_CHESS)
	{
		Location location(computerX - 1, computerY);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX - 1, computerY, depth - 1);
	}
	if (cm.isValid(computerX - 1, computerY + 1) && Computer::board[computerX - 1][computerY + 1] == NO_CHESS)
	{
		Location location(computerX - 1, computerY + 1);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX - 1, computerY + 1, depth - 1);
	}
	if (cm.isValid(computerX + 1, computerY - 1) && Computer::board[computerX + 1][computerY - 1] == NO_CHESS)
	{
		Location location(computerX + 1, computerY - 1);
		locations.push_back(location);
		getLocationsByRecursion(locations, computerX + 1, computerY - 1, depth - 1);
	}
}

//是否存在一个点可以使最长连接步被堵死
string PlayChess_Start::isExistTruncationIndex(const int board[][COLUMN],int whoPlayer)
{
	int(*newBoard)[COLUMN] = new int[ROW][COLUMN];
	cm.copyTwoArray(newBoard, board);
	int maxLength = fa.getMaxLength_Actual(newBoard, whoPlayer);
	std::vector<Location> locations = cm.getEmptyLocationOnBoard(newBoard);
	for (int i = 0; i < locations.size(); i++)
	{
		fa.makeMove(Move(locations.at(i), cm.getOtherPlayer(whoPlayer)),newBoard);
		int currentLength = fa.getMaxLength_Actual(newBoard, whoPlayer);
		fa.unMakeMove(Move(locations.at(i), cm.getOtherPlayer(whoPlayer)), newBoard);
		if (maxLength - currentLength > ISCUTOFF)
		{
		/*	for (int m = 0; m < COLUMN; m++)
			{
				delete[] newBoard[m];
			}*/
		//	delete[] newBoard;
			return tf.getInputString(locations.at(i).getX(), locations.at(i).getY());
		}
	}
	/*for (int m = 0; m < COLUMN; m++)
	{
		delete[] newBoard[m];
	}*/
//	delete[] newBoard;
	return "";
}

/*描述：己方为从上到下下棋时的经验走法
  参数：为对手的上一步下棋位置
*/
string PlayChess_Start::playChess_TopToBottom(string lastStr){
	int split = lastStr.find(" ");
	int computerY = tf.getInt(lastStr.substr(split + 1, lastStr.length() - split - 1));
	int computerX = tf.getInt(lastStr.substr(0, lastStr.length() - (lastStr.length() - split)));

	if (computerY <= 5){
		if (tf.judgeIndexIsValid(computerX + 1, computerY - 2)){
			return tf.getInputString(computerX + 1, computerY - 2);
		}
		else if (tf.judgeIndexIsValid(computerX, computerY - 1)){
			return tf.getInputString(computerX, computerY - 1);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY - 1)){
			return tf.getInputString(computerX + 1, computerY - 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY + 2)){
			return tf.getInputString(computerX - 1, computerY + 2);
		}
		else if (tf.judgeIndexIsValid(computerX, computerY + 1)){
			return tf.getInputString(computerX, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY + 1)){
			return tf.getInputString(computerX - 1, computerY + 1);
		}
		else{
			return tf.getInputString(5, 5);
		}
	}
	else{
		if (tf.judgeIndexIsValid(computerX - 1, computerY + 2)){
			return tf.getInputString(computerX - 1, computerY + 2);
		}
		else if (tf.judgeIndexIsValid(computerX, computerY + 1)){
			return tf.getInputString(computerX, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY + 1)){
			return tf.getInputString(computerX - 1, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY - 2)){
			return tf.getInputString(computerX + 1, computerY - 2);
		}
		else if (tf.judgeIndexIsValid(computerX, computerY - 1)){
			return tf.getInputString(computerX, computerY - 1);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY - 1)){
			return tf.getInputString(computerX + 1, computerY - 1);
		}
		else{
			return tf.getInputString(5, 5);
		}
	}
}

/*描述：己方为从左到右下棋时的经验走法
参数：为对手的上一步下棋位置
*/
std::string PlayChess_Start::playChess_LeftToRight(std::string lastStr)
{
	int split = lastStr.find(" ");
	int computerY = tf.getInt(lastStr.substr(split + 1, lastStr.length() - split - 1));
	int computerX = tf.getInt(lastStr.substr(0, lastStr.length() - (lastStr.length() - split)));
	if (computerX <= 5)
	{
		if (tf.judgeIndexIsValid(computerX - 2, computerY + 1))
		{
			return tf.getInputString(computerX - 2, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY))
		{
			return tf.getInputString(computerX - 1, computerY);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY + 1))
		{
			return tf.getInputString(computerX - 1, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX + 2, computerY - 1))
		{
			return tf.getInputString(computerX + 2, computerY - 1);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY))
		{
			return tf.getInputString(computerX + 1, computerY);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY - 1))
		{
			return tf.getInputString(computerX + 1, computerY - 1);
		}
		else
		{
			return tf.getInputString(5, 5);
		}

	}
	else
	{
		if (tf.judgeIndexIsValid(computerX + 2, computerY - 1))
		{
			return tf.getInputString(computerX + 2, computerY - 1);

		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY))
		{
			return tf.getInputString(computerX + 1, computerY);
		}
		else if (tf.judgeIndexIsValid(computerX + 1, computerY - 1))
		{
			return tf.getInputString(computerX + 1, computerY - 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 2, computerY + 1))
		{
			return tf.getInputString(computerX - 2, computerY + 1);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY))
		{
			return tf.getInputString(computerX - 1, computerY);
		}
		else if (tf.judgeIndexIsValid(computerX - 1, computerY + 1))
		{
			return tf.getInputString(computerX - 1, computerY + 1);
		}
		else
		{
			return tf.getInputString(5, 5);
		}
	}
}
