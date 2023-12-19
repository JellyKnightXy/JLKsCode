#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#define max 10
using namespace std;
/*
*	Astar�㷨�����ŵ�����̰��
* ����ÿ�߳�ȥһ����Ҫ���Լ��߹���·��ʣ�µ�·��������������
* ������ʽ����
* f=g+h;
* fΪ���յĴ���
* gΪ�Ѿ������Ĵ���
* hΪԤ�Ƹ����Ĵ��ۣ����ֱ�߾��룬�������������ϰ��ֻ���������ֱ�߾��룬���ܼ���������б��
*/

//��ô���Ǻ��ļ���ÿһ���ľ��뼴��


//������һ����Ӧ�ô������Щ��Ϣ
struct nextpoint
{
	//��������g
	double g;
	//��������h
	int h;
	//��һ���������
	int x;
	int y;
};

//��������
int cheese[max][max];

//������һ���ľ���
int nextx[3] = { -1,0,1 };
int nexty[3] = { -1,0,1 };

//����һ���յ�
int fx, fy;

//�ж���һ��������
bool TfNextPoint(int x, int y)
{
	if (cheese[x][y] != -1&&x>=0&&y>=0)
	{
		return true;
	}
	return false;
}

//����g
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

//����h
int calh(int x, int y)
{
	int h;
	h = fabs(fx - x)+fabs(fy-y);
	return h;
}

//�����ĸ��¸����ֵ��С���������������е��±�index
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

//��ӡ����
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

//A*�㷨
void Astar(int x, int y)
{
	//�������Щ��Ϣ������
	struct nextpoint* NP = (struct nextpoint*)malloc(sizeof(struct nextpoint) * 9);
	//��������յ�ݹ����
	if (x == fx && y == fy)
	{
		cout << "Ѱ·�ɹ�����ͼ��ʾΪ��"<<endl;
		myprint();
		return;
	}
	//�Խ����������ߵĵ������������
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//�������������������ԭ��
			if (i + j)
			{
				//�ж���һ����������
				if (TfNextPoint(x + nextx[i], y + nexty[j]))
				{
					NP[count].g = calg(nextx[i], nexty[j]);
					NP[count].h = calh(x + nextx[i], y + nexty[j]);
					NP[count].x = x + nextx[i];
					NP[count].y = y + nexty[j];
				}
				else
				{
					//�������㲻���ߣ��ͱ�ʾ���ϰ���,���ǾͰ��������ж����ó�Ϊ-1
					NP[count].g = -1;
					NP[count].h = -1;
					NP[count].x = -1;
					NP[count].y = -1;
				}
			}
			count++;
		}
	}
	//������֮��ɸѡ����õ��Ǹ���
	int ans=getNext(NP);
	int nx = NP[ans].x;
	int ny = NP[ans].y;
	//��ʶ�Ѿ��߹���
	cheese[nx][ny] = 1;
	//������ֿ��ٵĿռ�
	free(NP);
	NP = NULL;
	//�ݹ����Ѱ����һ����õĵ�
	Astar(nx, ny);
}
//������
int main()
{
	cheese[max][max] = { 0 };
	int ix, iy;
	cout << "���������������꣺";
	cin >> ix >> iy;
	cout << "�����ʼ���յ����꣺";
	cin >> fx >> fy;
	cout << "��������������Ӽ����ϰ��㣺";
	int z;
	cin >> z;
	cout << "���ڽ�������z����������Ҫ���ϰ�������꣺"<<endl;
	for (int i = 0; i < z; i++)
	{
		int zx, zy;
		cin >> zx>>zy;
		cheese[zx][zy] = -1;
	}
	cout << "����ȷ�����ڵĵ�ͼ��ʽΪ��"<<endl;
	cheese[ix][iy] = 1;
	myprint();
	cout << "��ʼ���ɹ�����ʼѰ·:";
	Astar(ix, iy);
	return 0;
}
