/*

��Ŀ��
    ÿ���ڵ㶼��bugs��ֻ�а�ȫ��bugs�����˲��ܻ�þ��飬����ÿ��ֻ������20��
    bugs������n-1�����Լ�ÿ���ڵ��bugs��Ŀ�Լ����ǵ���Ӧ���飬�����ʹ�þ���
    ���

����:
    ���ϱ����������Ǵӽڵ�1���������Էֺܶ�֧��ȥ��Ľڵ㡣ÿ���ڵ���ö�ά����
    ��¼�Ե�ǰ�ڵ�iʱ����Ϊj��ʱ������Ž⣬Ȼ��DFS�Զ����£���Ҷ�ӽڵ��������
    ���¡�ת�Ʒ���Ϊdp[i][j] = dp[i][i-j] + dp[y][j]

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int X = 105;

int p[X],b[X],n,m;
vector<int> adj[X];
bool use[X];
int dp[X][X];

void dfs(int x)
{
    use[x] = true;
    int temp = (b[x]+19)/20;
    for(int i=temp;i<=m;i++)
        dp[x][i] = p[x];
    int y;
    int len = adj[x].size();
    for(int k=0;k<len;k++)
    {
        y = adj[x][k];
        if(use[y])
            continue;
        dfs(y);
        for(int i=m;i>=temp;i--)
            for(int j=1;j+temp<=i;j++)
                dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        if(n==-1&&m==-1)
            break;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&b[i],&p[i]);
            adj[i].clear();
        }
        int x,y;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            adj[y].push_back(x);
            adj[x].push_back(y);
        }
        if(!m)
        {
            puts("0");
            continue;
        }
        memset(dp,0,sizeof(dp));
        memset(use,false,sizeof(use));
        dfs(1);
        cout<<dp[1][m]<<endl;
    }
    return 0;
}
