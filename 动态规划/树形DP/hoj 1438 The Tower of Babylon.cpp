/*

��Ŀ��
    ����n�������壬����ÿ�����������Ŀû�����ƣ�����Ҫ���ľ��Ҫ�������������ĳ��Ϳ�
    ���ñ�����Ĵ�����������δ��ľ��ʹ������������

����:
    ����ÿ�������嶼ֻ�����ַ�������������ͬ��ʱ���ǲ��ܴ��ľ�ģ��������Ƚ�ͼ������
    һ�����ε�ģ�ͣ�Ȼ����vector��¼���ӣ�Ȼ��ͨ��DFS���仯�ķ���������߶ȼ���

*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 105;

int n,m;
int dp[X];
vector<int> adj[X];

struct node
{
    int a,b,c;
    friend bool operator < (node a,node b)
    {
        return a.a>b.a||(a.a==b.a&&a.b>b.b)||(a.a==b.a&&a.b==b.a&&a.c>b.c);
    }
}p[X];

void add(int a,int b,int c)
{
    if(a<b)
        swap(a,b);
    p[n].a = a;
    p[n].b = b;
    p[n].c = c;
    n++;
}

int dfs(int x)
{
    int len = adj[x].size();
    if(dp[x])
        return dp[x];
    if(!len)
        return 0;
    int temp = 0;
    int y;
    for(int i=0;i<len;i++)
    {
        y = adj[x][i];
        temp = max(temp,p[y].c+dfs(y));
    }
    dp[x] = temp;
    return dp[x];
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    int ncase = 0;
    while(cin>>m,m)
    {
        n = 0;
        int qq = 3*m;
        for(int i=0;i<qq;i++)
            adj[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(x,z,y);
            add(y,z,x);
        }
        sort(p,p+n);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if(p[i].a>p[j].a&&p[i].b>p[j].b)
                    adj[i].push_back(j);
        int ans = 0;
        for(int i=0;i<n;i++)
            ans = max(ans,dfs(i)+p[i].c);
        printf("Case %d: maximum height = %d\n",++ncase,ans);
    }

    return 0;
}
