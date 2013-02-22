/*
�C���ֱ������׷N�Ϸ���eľ�ķ�ʽ��a��b�Ƿeľ�ľ�̖����
move a onto b
�ڌ�a�ᵽb��֮ǰ���Ȍ�a��b�ϵķeľ�Ż�ԭ���λ�ã����磺1�ͷŻ�1�����_ʼλ�D��
move a over b
�ڌ�a�ᵽb���ڵ��Ƕѷeľ֮��֮ǰ���Ȍ�a�ϵķeľ�Ż�ԭ���λ�D��b���ڵ��Ƕѷeľ���ӣ�
pile a onto b
��a��������ϵķeľһ��ŵ�b�ϣ��ڰ�֮ǰb�Ϸ��ķeľ�Ż�ԭλ
pile a over b
��a��������ϵķeľһ��ᵽ��b���ڵ��Ƕѷeľ֮��
quit
�����Y��
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
{//�ڌ�a�ᵽb��֮ǰ���Ȍ�a��b�ϵķeľ�Ż�ԭ���λ�ã����磺1�ͷŻ�1�����_ʼλ�D��
	int cur;
	for(int i=top[x];i>=0;i--)	//��a�ϵĻ�ľ�Ż�ԭ���λ��
	{
		top[x]--;			//�ȼ�1
		cur = len[x][i];
		if(cur!=a)
		{
			len[cur][++top[cur]] = cur;	//��a�ϵĻ�ľ�Ż���������ڵ�λ��
			f[cur] = cur;				//��Ǹû�ľ���ڵ�λ��
		}
		else
			break;
	}
	for(int i=top[y];i>=0;i--)	//��b�ϵĻ�ľ�Ż�ԭ���λ��
	{
		cur = len[y][i];
		if(cur!=b)
		{
			len[cur][++top[cur]] = cur;
			f[cur] = cur;
		}
		else
			break;
		top[y]--;		//���һ����Ϊ��ľb���÷Ż����Լ������λ��
	}
	len[y][++top[y]] = a;
	f[a] = y;
}
void move_over()
{//�ڌ�a�ᵽb���ڵ��Ƕѷeľ֮��֮ǰ���Ȍ�a�ϵķeľ�Ż�ԭ���λ�D��b���ڵ��Ƕѷeľ���ӣ�
	int c;
	for(int i=top[x];i>=0;i--)		//�Ȍ�a�ϵķeľ�Ż�ԭ���λ�D
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
	len[y][++top[y]] = a;		//ֱ�Ӱ�a�ŵ�b�����϶�
	f[a] = y;
}
void pile_onto()
{//��a��������ϵķeľһ��ŵ�b�ϣ��ڰ�֮ǰb�Ϸ��ķeľ�Ż�ԭλ
	int c;
	for(int i=top[y];i>=0;i--)		//b�Ϸ��ķeľ�Ż�ԭλ
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
	for(int i=0;i<=cnt;i++)		//��a��������ϵķeľһ��ŵ�b��
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
{//��a��������ϵķeľһ��ᵽ��b���ڵ��Ƕѷeľ֮�ϣ�ͬ��
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