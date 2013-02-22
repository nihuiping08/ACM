/*

��Ŀ��
    ��n����Ʒ���ָ���m�ֹ�ϵ��ÿ�ֹ�ϵa,b��Ӧ����Ʒb�ܹ�����Ʒa������Ȼ����q��ѯ��(a,b)��
    ����Ʒa�ܲ��ܻ�����Ʒb��

������
    ���ֱ��dfs�󴫵ݱհ��Ļ����ᳬʱ�ġ����ǿ������½�ͼ��ʹ��ͼ��û�л�������ǿ��ͨ��֧
    �����������ڽӱ����½�ͼ��Ȼ��dfs�󴫵ݱհ�����

*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 5005;

int dfn[X],father[X],low[X],stack[X],depth,top,bcnt;
int n,m,t;
bool instack[X];
bool map[1005][1005];   //��ͼ�еĹ�ϵ
vector<int> adj[X];     //��ͼ
vector<int> nadj[X];    //��ͼ

void tarjan(int u)  //tarjan�㷨��ǿ��ͨ��֧
{
    int len,v;
    low[u] = dfn[u] = ++depth;
    stack[++top] = u;
    instack[u] = true;
    len = adj[u].size();
    for(int i=0;i<len;i++)
    {
        v = adj[u][i];
        if(!low[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
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
    memset(map,false,sizeof(map));

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);
    int len,v;
    for(int u=1;u<=n;u++)   //���½�ͼ
    {
        len = adj[u].size();
        for(int j=0;j<len;j++)
        {
            v = adj[u][j];
            if(father[u]!=father[v])//father��¼��������ͼ�еĶ���ţ���������ĺ��룩
                nadj[father[u]].push_back(father[v]);
        }
    }
}

void dfs(int u,int v)   //dfs�󴫵ݱհ�������floyd�Ļ��ᳬʱ
{
    int len = nadj[v].size();
    for(int i=0;i<len;i++)
        dfs(u,nadj[v][i]);
    map[u][v] = true;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)   //��ʼ��
        {
            adj[i].clear();
            nadj[i].clear();
        }
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            adj[u].push_back(v);
        }
        solve();
        for(int i=1;i<=bcnt;i++)    //�󴫵ݱհ�
            dfs(i,i);

        scanf("%d",&t);
        while(t--)
        {
            scanf("%d%d",&u,&v);
            if(father[u]==father[v])
            {
                printf("Yes\n");
                continue;
            }
            if(map[father[u]][father[v]])
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}
