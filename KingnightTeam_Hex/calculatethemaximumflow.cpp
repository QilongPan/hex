#include "calculatethemaximumflow.h"
/*
 * 计算最大流
*/
CalculateTheMaximumFlow::CalculateTheMaximumFlow()
{

}

void CalculateTheMaximumFlow::Ford_Fulkerson(int **c, int vertexNum, int s, int t, int **f)
{
    int *e = (int *)malloc(sizeof(int)*vertexNum*vertexNum);    // 残存网络
    int *priorMatrix = (int *)malloc(sizeof(int)*vertexNum);    // 增广路径的前驱子图

    // initialize
    for (int i = 0; i < vertexNum;i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            *(f + i*vertexNum + j) = 0;
        }
    }

    while (1)
    {
        calculateENet(c, vertexNum, (int **)f, (int **)e);  // 计算残存网络
        int min;
        if ((min = findRoute((int **)e, vertexNum, priorMatrix, s, t)) == 0)    // 寻找增广路径及其最小流值
        {
            break;
        }
        int pre = priorMatrix[t - 1];
        int next = t - 1;
        while (pre != -1)       // 按增广路径更新流网络
        {
            if (*((int*)c + pre * vertexNum + next) != 0)
            {
                *((int*)f + pre * vertexNum + next) += min;
            }
            else
            {
                *((int*)f + next * vertexNum + pre) -= min;
            }
            next = pre;
            pre = priorMatrix[pre];
        }
    }
}

// 计算残存网络
void CalculateTheMaximumFlow::calculateENet(int **c, int vertexNum, int **f, int **e)
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            int a = *((int*)c + i*vertexNum + j);
            if (a != 0)
            {
                *((int*)e + i*vertexNum + j) = a - *((int*)f + i*vertexNum + j);
                *((int*)e + j*vertexNum + i) = *((int*)f + i*vertexNum + j);
            }
            else
            {
                *((int*)e + i*vertexNum + j) = 0;
            }
        }
    }
}
// 寻找增广路径
int CalculateTheMaximumFlow::findRoute(int **e, int vertexNum, int *priorMatrix, int s,int t)
{
    s--; t--;
    int *d = (int *)malloc(sizeof(int)*vertexNum);
    // initialize
    for (int i = 0; i < vertexNum; i++)
    {
        d[i] = 0;
        priorMatrix[i] = -1;
    }
    d[s] = 1;
    // 反复用边<i,j>做松弛操作，将<s,...,j>更新为<s,...,i,j>
    for (int k = 0; k < vertexNum; k++)
    {
        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = 0; j < vertexNum; j++)
            {
                if (d[j] == 0)
                {
                    d[j] |= (d[i] & (*((int*)e + i*vertexNum + j) > 0));
                    if (d[j] == 1)
                    {
                        priorMatrix[j] = i;
                    }
                }
            }
        }
    }
    if (d[t] == 0)  return 0;

    int min = INT_MAX;
    int pre = priorMatrix[t];
    while (pre != -1)
    {
        if (min > *((int*)e + pre*vertexNum + t))
        {
            min = *((int*)e + pre*vertexNum + t);
        }
        t = pre;
        pre = priorMatrix[t];
    }
    return min;
}

//棋盘转为缩略图(thumbnail初始化为0)
void CalculateTheMaximumFlow::boardChangeToThumbnail(const int board[][COLUMN],int whoPlayer,int thumbnail[][INITMAPNUMBER]){
    for(int i = 0 ; i < INITMAPNUMBER; ++i){
        if(i == 0){     //为源节点
            for(int m = 0 ; m < COLUMN ; ++m){
                if(board[0][m] == NO_CHESS || board[0][m] == whoPlayer){
                    thumbnail[i][m+1] = 200;        //横坐标为源节点0，源节点为第一个点，所以第一行的节点会依次加1(初始流量为无限大)
                }
            }
        }
        else if((i >= (INITMAPNUMBER-12)) &&( i <= (INITMAPNUMBER-2))){      //棋盘最后一行
            int row = (i-1)/ROW;     //得到棋盘的横纵坐标
            int column = (i-1)%ROW;
            if(cm.isValid(row,column)&&board[row][column] == NO_CHESS){
                thumbnail[i][INITMAPNUMBER-1] = 200;
            }
			else if (cm.isValid(row, column) && board[row][column] == whoPlayer){
                 std::vector<int> points = getPointToPointVector(thumbnail,i);//得到指向该节点的点(point从0开始)
                 for(int k = 0; k < points.size(); ++k){
                     thumbnail[points.at(k)][INITMAPNUMBER-1] = 200; //将上面的点指向该点
                     thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
                 }
            }
        }
        else{
            int row = (i-1)/ROW;     //得到棋盘的横纵坐标
            int column = (i-1)%ROW;
			if (cm.isValid(row, column) && board[row][column] == NO_CHESS){
				//右边
                if(cm.isValid(row,column+1)&&(board[row][column+1] == NO_CHESS || board[row][column+1] == whoPlayer)){
                    thumbnail[i][i+1] = 1;  //第i个节点和i的右边个节点
                }
				//下边
                if(cm.isValid(row+1,column)&&(board[row+1][column] == NO_CHESS || board[row+1][column] == whoPlayer)){
                    thumbnail[i][i+11] = 1;  //第i个节点和i的下边个节点
                }
				//左下
                if(cm.isValid(row+1,column-1)&&(board[row+1][column-1] == NO_CHESS || board[row+1][column-1] ==whoPlayer)){
                   thumbnail[i][i+10] = 1;  //第i个节点和i的左下边节点
                }
            }
            else if(cm.isValid(row,column)&&board[row][column] == whoPlayer){       //如果该点为自己已下的点
                std::vector<int> points = getPointToPointVector(thumbnail,i);//得到指向该节点的点(point从0开始)
				//右边
                if(cm.isValid(row,column+1)&&(board[row][column+1] == NO_CHESS || board[row][column+1] == whoPlayer)){
                    for(int k = 0; k < points.size(); ++k){
                        thumbnail[points.at(k)][i+1] = thumbnail[points.at(k)][i]; //将上面的点指向该点
                        thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
                    }
                }
				//下边
                if(cm.isValid(row+1,column)&&(board[row+1][column] == NO_CHESS || board[row+1][column] == whoPlayer)){
                    for(int k = 0; k < points.size(); ++k){
                        thumbnail[points.at(k)][i+11] = thumbnail[points.at(k)][i]; //将上面的点指向该点
                        thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
                    }
                }
				//左下
                if(cm.isValid(row+1,column-1)&&(board[row+1][column-1] == NO_CHESS || board[row+1][column-1] ==whoPlayer)){
                    for(int k = 0; k < points.size(); ++k){
                        thumbnail[points.at(k)][i+10] = thumbnail[points.at(k)][i]; //将上面的点指向该点
                        thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
                    }
                }
            }
        }
    }
}

//棋盘转换为缩略图(从左到右)
void CalculateTheMaximumFlow::boardChangeToThumbnail_LeftToRight(const int board[][COLUMN], int whoPlayer, int thumbnail[][INITMAPNUMBER]){
	for (int i = 0; i < INITMAPNUMBER; ++i){
		if (i == 0){     //为源节点
			for (int m = 0; m < ROW; ++m){
				if (board[m][0] == NO_CHESS || board[m][0] == whoPlayer){
					thumbnail[i][m+1] = 200;        //横坐标为源节点0，源节点为第一个点，所以第一列的节点会依次加1(初始流量为无限大)
				}
			}
		}
		else if ((i >= (INITMAPNUMBER - 12)) && (i <= (INITMAPNUMBER - 2))){      //棋盘最后一l列
			int row = (i - 1) % ROW;     //得到棋盘的横纵坐标
			int column = (i - 1) / ROW;
			if (cm.isValid(row, column) && board[row][column] == NO_CHESS){
				thumbnail[i][INITMAPNUMBER - 1] = 200;
			}
			else if (cm.isValid(row, column) && board[row][column] == whoPlayer){
				std::vector<int> points = getPointToPointVector(thumbnail, i);//得到指向该节点的点(point从0开始)
				for (int k = 0; k < points.size(); ++k){
					thumbnail[points.at(k)][INITMAPNUMBER - 1] = 200; //将上面的点指向该点
					thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
				}
			}
		}
		else{
			int row = (i - 1) % ROW;     //得到棋盘的横纵坐标
			int column = (i - 1) / ROW;
			if (cm.isValid(row, column) && board[row][column] == NO_CHESS){
				//右边
				if (cm.isValid(row, column + 1) && (board[row][column + 1] == NO_CHESS || board[row][column + 1] == whoPlayer)){
					thumbnail[i][i + 11] = 1;  //第i个节点和i的右边个节点
				}
				//下边
				if (cm.isValid(row + 1, column) && (board[row + 1][column] == NO_CHESS || board[row + 1][column] == whoPlayer)){
					thumbnail[i][i + 1] = 1;  //第i个节点和i的下边个节点
				}
				//右上
				if (cm.isValid(row - 1, column + 1) && (board[row - 1][column + 1] == NO_CHESS || board[row - 1][column + 1] == whoPlayer)){
					thumbnail[i][i + 10] = 1;  //第i个节点和i的右上边节点
				}
			}
			else if (cm.isValid(row, column) && board[row][column] == whoPlayer){       //如果该点为自己已下的点
				std::vector<int> points = getPointToPointVector(thumbnail, i);//得到指向该节点的点(point从0开始)
				//右边
				if (cm.isValid(row, column + 1) && (board[row][column + 1] == NO_CHESS || board[row][column + 1] == whoPlayer)){
					for (int k = 0; k < points.size(); ++k){
						thumbnail[points.at(k)][i + 11] = thumbnail[points.at(k)][i]; //将上面的点指向该点
						thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
					}
				}
				//下边
				if (cm.isValid(row + 1, column) && (board[row + 1][column] == NO_CHESS || board[row + 1][column] == whoPlayer)){
					for (int k = 0; k < points.size(); ++k){
						thumbnail[points.at(k)][i + 1] = thumbnail[points.at(k)][i]; //将上面的点指向该点
						thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
					}
				}
				//右上
				if (cm.isValid(row - 1, column+ 1) && (board[row - 1][column + 1] == NO_CHESS || board[row - 1][column + 1] == whoPlayer)){
					for (int k = 0; k < points.size(); ++k){
						thumbnail[points.at(k)][i + 10] = thumbnail[points.at(k)][i]; //将上面的点指向该点
						thumbnail[points.at(k)][i] = 0;  //删除以前指向该点的点
					}
				}
			}
		}
	}
}

//得到指向该节点的点(point从0开始)
 std::vector<int> CalculateTheMaximumFlow::getPointToPointVector(const int thumbnail[][123],int point){
     std::vector<int> points;
     for(int i = 0; i < 123; ++i){
         if(thumbnail[i][point] > 0){
            points.push_back(i);
         }
     }
     return points;
 }

//获得图
int CalculateTheMaximumFlow::getFord(int board[][COLUMN],int whoPlayer){
    int test[INITMAPNUMBER][INITMAPNUMBER];     //图,第一个元素为自己添加的源节点，第最后一个元素为自己添加的接收节点
  /*  for(int i = 0 ; i < 123 ; i++){
        for(int j = 0 ; j < 123 ; j++){
            if(j <= i){
                test[i][j] = 0;
            }
            else{
                test[i][j] = getNodeFlow(i,j);
            }
        }
    }*/
	for (int i = 0; i < INITMAPNUMBER; i++){
		for (int j = 0; j < INITMAPNUMBER; j++){
			test[i][j] = 0;
		}
	}
	if (whoPlayer == Computer::onTheOffensiveValue){
		boardChangeToThumbnail(board, whoPlayer, test);
	}
	else{
		boardChangeToThumbnail_LeftToRight(board, whoPlayer, test);
	}
    int sumFlow=0;
	sumFlow = maxFlow(test, 0, 122);
    /*int f[INITMAPNUMBER][INITMAPNUMBER];
    Ford_Fulkerson((int **)test, 123, 1, 123, (int **)f);
    for (int i = 0; i < 123; i++)
    {
        for (int j = 0; j < 123; j++)
        {
            int flow = f[i][j];
            if (flow != 0)
            {
                sumFlow+=flow;
            }
        }
    }*/
    return sumFlow;
}

//得到一个节点到另一个节点的流量
int CalculateTheMaximumFlow::getNodeFlow(int start, int end){
    if(start == 0 && end == 0){     //源节点到源节点
        return 0;
    }
    //接收节点
    if(start == 123 && end == 123){
        return 0;
    }
    if(end == 122){
        if(start < 122 && start > 110){ //最后一行到接收节点
            return 1000;
        }
        else{
            return 0;
        }
    }

    if(start == 0){
        if(end < 12 && end > 0){//源节点到棋盘的第一行
            return 1000;
        }
        else{
            return 0;
        }
    }
    int startNodeRow = (start-1)/11;       //开始节点的横坐标
    int startNodeColumn = (start-1)%11; //开始节点的纵坐标
    int endNodeRow = (end-1)/11;
    int endNodeColumn = (end-1)%11;
    if(judgeIsAdjacent(startNodeRow,startNodeColumn,endNodeRow,endNodeColumn)){
        return 1;
    }
    else{
        return 0;
    }

}
//判断两个节点是否相邻
bool CalculateTheMaximumFlow::judgeIsAdjacent(int startNodeRow, int startNodeColumn, int endNodeRow, int endNodeColumn){
    if(Computer::board[startNodeRow][startNodeColumn] == PLAYER_CHESS){
        return false;
    }
    if(Computer::board[endNodeRow][endNodeColumn] == PLAYER_CHESS){
        return false;
    }
    //朝右
    if(startNodeRow == endNodeRow && ((startNodeColumn+1) == endNodeColumn)){
        return true;
    }
    //朝下
    if(((startNodeRow+1) == endNodeRow) && (startNodeColumn == endNodeColumn)){
        return true;
    }
    //朝左下
    if(((startNodeRow+1) == endNodeRow) && ((startNodeColumn-1) == endNodeColumn)){
        return true;
    }
    return false;
}

/*void testFord()
{
    int c[6][6] = { 0,      16,     13,     0,      0,      0,
                    0,      0,      0,      12,     0,      0,
                    0,      4,      0,      0,      14,     0,
                    0,      0,      9,      0,      0,      20,
                    0,      0,      0,      7,      0,      4,
                    0,      0,      0,      0,      0,      0   };
    int f[6][6];
    Ford_Fulkerson((int **)c, 6, 1, 6, (int **)f);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int flow = f[i][j];
            if (flow != 0)
            {
                printf("%d -> %d : %d\n", i + 1, j + 1, flow);
            }
        }
    }
}  */


bool CalculateTheMaximumFlow::hasPath(int rGraph[][INITMAPNUMBER], int s, int t, int path[]){
	bool visited[INITMAPNUMBER];
	for (int i = 0; i < INITMAPNUMBER; i++){
		visited[i] = false;
	}
	queue<int> que;
	que.push(s);
	visited[s] = true;
	while (que.size() > 0){
		int top = que.front();		//取出队列首元素
		que.pop();		//弹出队列的首元素
		for (int i = 0; i < INITMAPNUMBER; i++){
			if (!visited[i] && rGraph[top][i] > 0){
				que.push(i);
				visited[i] = true;
				path[i] = top;
			}
		}
	}
	return visited[t] == true;
}

int CalculateTheMaximumFlow::maxFlow(int graph[][INITMAPNUMBER], int s, int t){
	int rGraph[INITMAPNUMBER][INITMAPNUMBER];
	for (int i = 0; i < INITMAPNUMBER; i++){
		for (int j = 0; j < INITMAPNUMBER; j++){
			rGraph[i][j] = graph[i][j];
		}
	}
	int maxFlow = 0;
	int path[INITMAPNUMBER];
	while (hasPath(rGraph, s, t, path)){
		int min_flow = INT_MAX;
		//更新路径中的每条边，找到最小的流量
		for (int v = t; v != s; v = path[v]){
			int u = path[v];
			min_flow = min_flow < rGraph[u][v] ? min_flow : rGraph[u][v];
		}
		//更新路径中的每条边 
		for (int v = t; v != s; v = path[v]){
			int u = path[v];
			rGraph[u][v] -= min_flow;
			rGraph[v][u] += min_flow;
		}
		maxFlow += min_flow;
	}
	return maxFlow;
}