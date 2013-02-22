/*
题目：
	给出一个矩阵，然后给出m个密码串，问你这个密码串在矩阵中的出现位置以及他的方向，注意有八个方向。

分析：
	先对密码串建立AC自动机，然后枚举每个方向的最长串，看看能不能在AC自动机中出现过，若出现过则更新答案。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 100002;
const int X = 1001;
const int kind = 26;
#define debug cout<<"here"<<endl;

char map[X][X],str[X][X];
int n,m,qq;
int a[X],b[X],d[X];

int dir[8][2] ={{-1,-1},{-1,1},{1,-1},{1,1},{0,1},{0,-1},{1,0},{-1,0}};
char out[9] = "DFBHGCAE";

struct node
{
	node *p[kind];
	node *fail;
	int id;
	node()
	{
		id = -1;
		memset(p,NULL,sizeof(p));
		fail = NULL;
	}
}*q[maxn];

void insert(node *r,int cd,char *s)
{
	int id;
	for(int i=0;s[i];i++)
	{
		id = s[i]-'A';
		if(r->p[id]==NULL)
			r->p[id] = new node();
		r = r->p[id];
	}
	r->id = cd;
}

void ac_build(node *r)
{
	node *pre,*temp;
	int head,tail;
	head = tail = 0;
	r->fail = NULL;
	q[head++] = r;
	while(tail<head)
	{
		pre = q[tail++];
		for(int id=0;id<kind;id++)
		{
			if(pre->p[id])
			{
				temp = pre->fail;
				while(temp&&temp->p[id]==NULL)
					temp = temp->fail;
				if(temp)
					pre->p[id]->fail = temp->p[id];
				else
					pre->p[id]->fail = r;
				q[head++] = pre->p[id];
			}
		}
	}	
}

void ac_run(node *r,char *s,int x,int y,int cd)
{
	node *pre = r;
	node *temp;
	int id,ret;
	for(int j=0;s[j];j++)
	{
		id = s[j]-'A';
		while(pre!=r&&pre->p[id]==NULL)
			pre = pre->fail;
		pre = pre->p[id];
		if(pre==NULL)
			pre = r;
		temp = pre;
		while(temp!=r)
		{
			ret = temp->id;
			if(ret!=-1&&d[ret]==-1)
			{
				a[ret] = x;
				b[ret] = y;
				d[ret] = cd;
			}
			temp = temp->fail;
		}
		x += dir[cd][0];
		y += dir[cd][1];
	}
}

bool check(int x,int y)
{
	if(x<0||x>=n||y<0||y>=m)
		return false;
	return true;
}

void change(node *r,int cx,int cy,int dx,int dy,int direc)
{
	char s[X];
	int x,y,len;	
	x = cx;
	y = cy;
	    
	len = 0;
	while(check(x+dx,y+dy))
	{
		s[len++] = map[x][y];
		x += dx;
		y += dy;
	}
	s[len++] = map[x][y];
	s[len] = '\0';
	ac_run(r,s,cx,cy,direc);
}


int main()
{
	cin>>n>>m>>qq;
	getchar();
	for(int i=0;i<n;i++)
		gets(map[i]);
	node *r = new node();
	int l;
	char s[X],t[X];
	for(int i=0;i<qq;i++)
	{
		gets(str[i]);
		l = strlen(str[i]);
		for(int j=0;j<l;j++)
			s[j] = str[i][l-j-1];
		s[l] = '\0';
		insert(r,i,s);
	}
	ac_build(r);
	memset(d,-1,sizeof(d));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			s[j] = map[i][j];
		s[m] = '\0';	
		ac_run(r,s,i,0,4);
		for(int j=0;j<m;j++)
			s[j] = map[i][m-j-1];
		s[m] = '\0';
		ac_run(r,s,i,m-1,5);
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			s[j] = map[j][i];
			t[j] = map[n-j-1][i];
		}
		s[n] = t[n] = '\0';
		ac_run(r,s,0,i,6);
		ac_run(r,t,n-1,i,7);
	}
	for(int i=0;i<n;i++)
	{
		change(r,i,0,1,1,3);
		change(r,i,n-1,-1,-1,0);
		change(r,i,0,-1,1,1);
		change(r,i,n-1,1,-1,2);
	}
	for(int i=0;i<m;i++)
	{	
		change(r,0,i,1,1,3);
		change(r,n-1,i,-1,-1,0);
		change(r,0,i,1,-1,2);
		change(r,n-1,i,-1,1,1);
	}
	for(int i=0;i<qq;i++)
		printf("%d %d %c\n",a[i],b[i],out[d[i]]);

	return 0;
}