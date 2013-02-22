/*

��Ŀ��
	������������ʱ����Ҫ�������ǳԵ�һͷ���������ٳ���һͷ�����ǿ��ԳԵ�����������Ŀ

������
	�������ɶ���ͼ����iͷ���ܳԵ���jͷ����g[i][j] = true���ɽ�ͼ��������Ԥ����ÿһͷ�����
	����ţ�Ȼ���ٽ�ͼ

*/
#include <cstdio>
#include <cstring>
#define X 105
#define M 11
char ch[M][M];
int ym[X],cal[2][M][M],n,m,nw,np;
//int xm[X];
bool use[X],g[X][X];
bool dfs(int u)
{
	for(int v=1;v<=np;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			if(ym[v]==-1||dfs(ym[v]))
			{
				//xm[u] = v;
				ym[v] = u;
				return true;
			}
		}
		return false;
}
int hungry()
{
	//memset(xm,-1,sizeof(xm));
	memset(ym,-1,sizeof(ym));
	int ret = 0;
	for(int u=1;u<=nw;u++)
		//if(xm[u]==-1)
		{
			memset(use,false,sizeof(use));
			if(dfs(u))
				ret++;
		}
	return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(g,false,sizeof(g));
		memset(cal,0,sizeof(cal));
		for(int i=0;i<n;i++)
			scanf("%s",ch[i]);
		nw = np = 0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				if(ch[i][j]=='W')	//��ʾ���λ��Ϊ�ǣ����������Ϊ��++nwͷ
					cal[1][i][j] = ++nw;
				else if(ch[i][j]=='P')
					cal[0][i][j] = ++np;
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				if(ch[i][j]=='W')
					if(i>0&&ch[i-1][j]=='P')		//����Ϊ��Ļ�
						g[cal[1][i][j]][cal[0][i-1][j]] = true;
					else if(i<n-1&&ch[i+1][j]=='P')	//��
						g[cal[1][i][j]][cal[0][i+1][j]] = true;
					else if(j>0&&ch[i][j-1]=='P')	//��
						g[cal[1][i][j]][cal[0][i][j-1]] = true;
					else if(j<m-1&&ch[i][j+1]=='P')	//��
						g[cal[1][i][j]][cal[0][i][j+1]] = true;
		}
		printf("%d\n",hungry());
	}

	return 0;
}