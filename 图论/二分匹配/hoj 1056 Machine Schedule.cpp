/*

���⣺���⻹�ǱȽϼ򵥣��кܶ�job��������machine A����machine B��ĳ��modeֻ���ڶ���ͼƥ���
ʱ���ÿ��ǵ�һ�����������ĳ�ʼ״̬���Ը�����Ҫ���е��������Ǳ��ж��������ˡ�

���룺����Ƚ��˷���Դ��k��������ϵ���Ͳ���ÿ�л������к��˰ɣ�

��������ƥ������

˼·��������Hungary�㷨������machine A��mode��machine B��mode������һ������ͼ�������ڲ�֮��
�����бߣ����ĳ�����������machine A��mode x����machine B��mode y��ɣ���ô��x��y��һ���ߣ�
��(x,y) = true��Ȼ��������ƥ�伴�ɡ�


*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 102
int xm[X],ym[X],n,m;
bool map[X][X],use[X];
int dfs(int u)
{
	for(int i=0;i<m;i++)
		if(map[u][i]&&!use[i])
		{
			use[i] = true;
			if(ym[i]==-1||dfs(ym[i]))
			{
				xm[u] = i;
				ym[i] = u;
				return true;
			}
		}
		return false;
}
int hungry()
{
	int ret = 0;
	memset(xm,-1,sizeof(xm));
	memset(ym,-1,sizeof(ym));
	for(int i=0;i<n;i++)
		if(xm[i]==-1)
		{
			memset(use,false,sizeof(use));
			if(dfs(i))
				ret++;
		}
		return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int k,x,y,z;
	while(cin>>n,n)
	{
		cin>>m>>k;
		memset(map,false,sizeof(map));
		for(int i=0;i<k;i++)
		{
			scanf("%d%d%d",&z,&x,&y);
			if(x&&y)
				map[x][y] = true;
		}
		printf("%d\n",hungry());
	}

	return 0;
}