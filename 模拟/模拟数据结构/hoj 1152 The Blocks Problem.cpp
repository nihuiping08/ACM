/*
機器手臂有以下幾種合法搬積木的方式（a和b是積木的編號）：
move a onto b
在將a搬到b上之前，先將a和b上的積木放回原來的位置（例如：1就放回1的最開始位罝）
move a over b
在將a搬到b所在的那堆積木之上之前，先將a上的積木放回原來的位罝（b所在的那堆積木不動）
pile a onto b
將a本身和其上的積木一起放到b上，在搬之前b上方的積木放回原位
pile a over b
將a本身和其上的積木一起搬到到b所在的那堆積木之上
quit
動作結束
*/
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
const int X = 26;
string s1,s2;
int len[X][X],c[X],top[X],f[X],a,b,n,x,y;
void move_onto()
{//在將a搬到b上之前，先將a和b上的積木放回原來的位置（例如：1就放回1的最開始位罝）
	int cur;
	for(int i=top[x];i>=0;i--)	//把a上的积木放回原來的位置
	{
		top[x]--;			//先减1
		cur = len[x][i];
		if(cur!=a)
		{
			len[cur][++top[cur]] = cur;	//把a上的积木放回它最初所在的位置
			f[cur] = cur;				//标记该积木所在的位置
		}
		else
			break;
	}
	for(int i=top[y];i>=0;i--)	//把b上的积木放回原來的位置
	{
		cur = len[y][i];
		if(cur!=b)
		{
			len[cur][++top[cur]] = cur;
			f[cur] = cur;
		}
		else
			break;
		top[y]--;		//后减一，因为积木b不用放回他自己最初的位置
	}
	len[y][++top[y]] = a;
	f[a] = y;
}
void move_over()
{//在將a搬到b所在的那堆積木之上之前，先將a上的積木放回原來的位罝（b所在的那堆積木不動）
	int c;
	for(int i=top[x];i>=0;i--)		//先將a上的積木放回原來的位罝
	{
		top[x]--;
		c = len[x][i];
		if(c!=a)
		{
			len[c][++top[c]] = c;
			f[c] = c;
		}
		else
			break;
	}
	len[y][++top[y]] = a;		//直接把a放到b的最上端
	f[a] = y;
}
void pile_onto()
{//將a本身和其上的積木一起放到b上，在搬之前b上方的積木放回原位
	int c;
	for(int i=top[y];i>=0;i--)		//b上方的積木放回原位
	{
		c = len[y][i];
		if(c!=b)
		{
			len[c][++top[c]] = c;
			f[c] = c;
		}
		else
			break;
		top[y]--;
	}
	bool flag = false;
	int cnt = top[x];
	for(int i=0;i<=cnt;i++)		//將a本身和其上的積木一起放到b上
	{
		c = len[x][i];
		if(c==a)
		{
			flag = true;
			top[x] = i-1;
		}
		if(flag)
		{
			len[y][++top[y]] = c;
			f[c] = y;
		}
	}
}
void pile_over()
{//將a本身和其上的積木一起搬到到b所在的那堆積木之上，同理
	bool flag = false;
	int c;
	int cnt = top[x];
	for(int i=0;i<=cnt;i++)
	{
		c = len[x][i];
		if(c==a)
		{
			flag = true;
			top[x] = i-1;
		}
		if(flag)
		{
			len[y][++top[y]] = c;
			f[c] = y;
		}
	}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n)
	{
		memset(top,0,sizeof(top));
		for(int i=0;i<n;i++)
		{
			len[i][0] = i;
			f[i] = i;
		}
		while(cin>>s1,s1!="quit")
		{
			cin>>a>>s2>>b;
			x = f[a];
			y = f[b];
			if(s1=="move")
			{
				if(s2=="onto")
					move_onto();
				else
					move_over();
			}
			else
			{
				if(s2=="onto")
					pile_onto();
				else
					pile_over();
			}
		}
		for(int i=0;i<n;i++)
		{
			printf("%d:",i);
			for(int j=0;j<=top[i];j++)
				cout<<" "<<len[i][j];
			cout<<endl;
		}
	}
	return 0;
}