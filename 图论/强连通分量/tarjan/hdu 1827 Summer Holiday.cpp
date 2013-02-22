/*

��Ŀ��
    ��˵lcy����Ԥ��������̩7���Σ�Wiskey���Ǹ��˵�ҹ�����°��������ŵÿ��
    ������Ϣ���ߴ�ң���Ȼ�������������˵���ϵ��ʽ������һ��һ����ϵ��ȥʵ��
    ̫��ʱ��͵绰���ˡ���֪��������Ҳ��һЩ���˵���ϵ��ʽ������������֪ͨ��
    ���ˣ����������˰�æ֪ͨһ�±��ˡ����ܰ�Wiskey���������Ҫ֪ͨ�����ˣ���
    �ٵû����ٵ绰�Ѿ����������˶���֪ͨ����

������
    ��Ϊ����ͨ����������֪ͨ������ʶ���ˣ��������ͼ������ǿ��ͨ�������һ��
    �����ͼ�������໥ǿ��ͨ��֧���һ�����㣬����������������Ϊ0�����㼴Ϊ
    �������Ҫ֪ͨ����С������Ȼ����ö�����������ڵ������Ƿ����Ϊ0���ǵĻ���
    �¸������������С���ü���


*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int V = 1005;
const int INF = 1e9;

vector<int> adj[V];

int cost[V],n,m;
int dfn[V],low[V],father[V],stack[V],bcnt,depth,top;
bool instack[V];
int id[V],cnt[V];

void dfs(int u) //tarjan������
{
    instack[u] = true;
    low[u] = dfn[u] = ++depth;
    stack[++top] = u;
    int v;
    int len = adj[u].size();
    for(int i=0;i<len;i++)
    {
        v = adj[u][i];
        if(!low[v])
        {
            dfs(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++bcnt;
        do
        {
            v = stack[top--];
            instack[v] = false;
            father[v] = bcnt;
        }while(u!=v);
    }
}

void solve()
{
    depth = top = bcnt = 0;
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    for(int i=1;i<=n;i++)
        if(!low[i])
            dfs(i);

    memset(id,0,sizeof(id));
    int v,len;
    for(int i=1;i<=n;i++)   //ͳ��������������
    {
        len = adj[i].size();
        for(int j=0;j<len;j++)
        {
            v = adj[i][j];
            if(father[i]!=father[v])
                id[father[v]]++;
        }
    }
    int ci = 0;
    int ans = 0;
    for(int i=1;i<=bcnt;i++)    //�������Ŀ��Ϊbcnt
    {
        if(id[i]==0)    //ͳ�����Ϊ0����Ŀ
            ci++;
        cnt[i] = INF;
    }
    for(int i=1;i<=n;i++)
    {
        v = father[i];
        if(id[v]==0)
            cnt[v] = min(cnt[v],cost[i]);   //���·���
    }
    for(int i=1;i<=bcnt;i++)
        if(cnt[i]!=INF)
            ans += cnt[i];
    printf("%d %d\n",ci,ans);
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&cost[i]);
            adj[i].clear();
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            adj[x].push_back(y);
        }
        solve();
    }
    return 0;
}
