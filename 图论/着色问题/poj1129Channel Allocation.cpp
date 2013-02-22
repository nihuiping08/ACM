#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
#define X 305
string s;
int map[X][X],color[X],n,x,y,len,c,ans;
bool check(int a,int col)	//��鶥��a����ɫ�ܷ�Ϳ��col
{
	for(int i=1;i<=n;i++)
		if(map[a][i]&&color[i]==col)	//���ڽڵ���ɫ����һ��������
			return false;
	return true;
}
bool dfs(int tc,int v)	//������ɫ����Ϊtcʱ������ҪͿɫ���Ƕ���v
{
	if(tc==n)	//�����ɫ��������n����Ϊ֮ǰ���ý��ٵ���ɫ������Ϳ�ã����Դ˴���ֱ�ӷ�����
		return true;
	if(v==n+1)	//�����n���ڵ㶼Ϳ��Ļ���ֱ�ӷ�����
		return true;
	for(int i=1;i<=tc;i++)	//����ɫ1��ʼö�٣�������ǰ��ɫ�Ƿ���Ϳ�����ж���
	{
		color[v] = i;
		if(check(v,i))	//�ж��Ƿ����Ϳ����ɫi
			if(dfs(tc,v+1))	//�������Ķ���ͬ����Ϳ�ã�������
				return true;
	}
	return false;
}
int solve()	//����ƽ��ͼ��4ɫ����ö����ɫ1��4����
{
	//////ֱ����1����ɫ�����Ƿ���Ϳ��
	bool flag = true;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(map[i][j])
				flag = false;
	if(flag)
		return 1;

	for(int i=2;i<=4;i++)	//��2��ʼö��
	{
		memset(color,0,sizeof(color));
		if(dfs(i,1))
			return i;
	}
	return -1;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		ans = 1;
		memset(map,0,sizeof(map));
		for(int i=0;i<n;i++)
		{
			cin>>s;
			len = s.size();
			x = s[0] - 'A'+1;	//ת��Ϊͼ���ڽӾ����ʾ��ʽ�����±��1��ʼ
			for(int j=2;j<len;j++)
			{
				c = s[j]-'A'+1;
				map[x][c] = map[c][x] = 1;
			}
		}
		int ans = solve();
		if(ans==1)
			printf("1 channel needed.\n");
		else
			printf("%d channels needed.\n",ans);
	}
	return 0;
}