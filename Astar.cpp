#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#define max 10
using namespace std;
/*
*	Astar算法的有优点在于贪心
* 我们每走出去一步都要对自己走过的路和剩下的路，进行量化评估
* 评估公式就是
* f=g+h;
* f为最终的代价
* g为已经付出的代价
* h为预计付出的代价，求出直线距离，并且无视所有障碍物，只计算两点间直线距离，不能计算相连的斜线
*/

//那么我们核心计算每一步的距离即可


//定义下一个点应该储存好哪些信息
struct nextpoint
{
	//评估距离g
	double g;
	//评估距离h
	int h;
	//下一个点的坐标
	int x;
	int y;
};

//定义棋盘
int cheese[max][max];

//定义下一步的距离
int nextx[3] = { -1,0,1 };
int nexty[3] = { -1,0,1 };

//定义一下终点
int fx, fy;

//判断下一步能走吗
bool TfNextPoint(int x, int y)
{
	if (cheese[x][y] != -1&&x>=0&&y>=0)
	{
		return true;
	}
	return false;
}

//计算g
double calg(int x, int y)
{
	double g;
	if (x * y > 0)
	{
		g = (fabs(x) + fabs(y)) * 1.4;
	}
	g = fabs(x) + fabs(y);
	return g;
}

//计算h
int calh(int x, int y)
{
	int h;
	h = fabs(fx - x)+fabs(fy-y);
	return h;
}

//搜索哪个下个点的值最小，返回他在数列中的下标index
int getNext(struct nextpoint* np)
{
	double ans = max*max;
	int index = 1;
	for (int i = 1; i < 9; i++)
	{
		if (np[i].g + np[i].h <= ans&&np[i].g>=0)
		{
			ans = np[i].g + np[i].h;
			index = i;
		}
	}
	return index;
}

//打印函数
void myprint()
{
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			printf("%d ", cheese[i][j]);
		}
		printf("\n");
	}
}

//A*算法
void Astar(int x, int y)
{
	//定义好这些信息的数组
	struct nextpoint* NP = (struct nextpoint*)malloc(sizeof(struct nextpoint) * 9);
	//如果到达终点递归结束
	if (x == fx && y == fy)
	{
		cout << "寻路成功，地图显示为："<<endl;
		myprint();
		return;
	}
	//对接下来可能走的点进行量化评估
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//不能让我们这个点留在原地
			if (i + j)
			{
				//判断下一个点能走吗
				if (TfNextPoint(x + nextx[i], y + nexty[j]))
				{
					NP[count].g = calg(nextx[i], nexty[j]);
					NP[count].h = calh(x + nextx[i], y + nexty[j]);
					NP[count].x = x + nextx[i];
					NP[count].y = y + nexty[j];
				}
				else
				{
					//如果这个点不能走，就表示是障碍物,我们就把他的所有都设置成为-1
					NP[count].g = -1;
					NP[count].h = -1;
					NP[count].x = -1;
					NP[count].y = -1;
				}
			}
			count++;
		}
	}
	//评估完之后筛选出最好的那个点
	int ans=getNext(NP);
	int nx = NP[ans].x;
	int ny = NP[ans].y;
	//标识已经走过了
	cheese[nx][ny] = 1;
	//清除本轮开辟的空间
	free(NP);
	NP = NULL;
	//递归调用寻找下一个最好的点
	Astar(nx, ny);
}
//主函数
int main()
{
	cheese[max][max] = { 0 };
	int ix, iy;
	cout << "请你输入起点的坐标：";
	cin >> ix >> iy;
	cout << "请你初始化终点坐标：";
	cin >> fx >> fy;
	cout << "请你输入你想添加几个障碍点：";
	int z;
	cin >> z;
	cout << "请在接下来的z行里，输出你想要的障碍点的坐标："<<endl;
	for (int i = 0; i < z; i++)
	{
		int zx, zy;
		cin >> zx>>zy;
		cheese[zx][zy] = -1;
	}
	cout << "请你确认现在的地图样式为："<<endl;
	cheese[ix][iy] = 1;
	myprint();
	cout << "初始化成功，开始寻路:";
	Astar(ix, iy);
	return 0;
}
