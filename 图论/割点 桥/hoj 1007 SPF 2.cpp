/*

��Ŀ��
    ����ͼ����

������
    tarjan�㷨ʵ�֣�ÿ�α������ö���ʱ����¼������ʱ����Լ����Ķ��ӽڵ��ܹ�
    �������͵�ʱ���������lowֵ������ʱ���dfn��Ҫ��Ļ���˵�������Ķ��Ӳ�
    �ܹ��������ĸ��׽ڵ㣬˵������һ�����

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1005;

int map[X][X];
bool use[X];
int n,m,ans[X],stack[X],depth,dfn[X],low[X];

void dfs(int x)
{
    dfn[x] = low[x] = ++depth;
    for(int i=1;i<=n;i++)
    {
        if(map[x][i]==1)
        {
            map[x][i] = map[i][x] = 2;
            if(!dfn[i])
            {
                dfs(i);
                low[x] = min(low[x],low[i]);
                if(low[i]>=dfn[x])
                    ans[x]++;
            }
            else
                low[x] = min(low[x],dfn[i]);
        }
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y;
    int ncase = 0;
    while(cin>>x,x)
    {
        if(ncase)
            puts("");
        printf("Network #%d\n",++ncase);
        cin>>y;
        memset(map,0,sizeof(map));
        map[x][y] = map[y][x] = 1;
        n = max(x,y);
        while(scanf("%d",&x),x)
        {
            scanf("%d",&y);
            n = max(n,max(x,y));
            map[x][y] = map[y][x] = 1;
        }
        memset(dfn,0,sizeof(dfn));
        memset(ans,0,sizeof(ans));
        dfs(1);
        ans[1]--;
        bool ok = false;
        for(int i=1;i<=n;i++)
            if(ans[i]>0)
            {
                printf("  SPF node %d leaves %d subnets\n",i,ans[i]+1);
                ok = true;
            }
        if(!ok)
            printf("  No SPF nodes\n");
    }
    return 0;
}
