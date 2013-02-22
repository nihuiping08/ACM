/*

2-SAT����һ��ָ���������⣺2n��������Է�Ϊn�飬ÿ��2�����㣬��������
����ֻ��ѡ������һ�������������������ѡ�˶���a�󣬱���ѡ��b�������
һ�������(a,b)
�����У�n�Է���(�������ɺ����ǡ�ÿ��Դ���n��㣬Ů�ı�Ϊ0��2...��
�ı�Ϊ1,3...ÿ�Է��ޣ�ֻ��ѡһ����������Ķ���,��ѡ��һ�����ʾ�õ���
����Ķ��棬����������ϵx,y����ӱ�(x,~y),(y,~x)�����ӱ�(0,1)

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 200;
#define debug puts("here");

int father[X],stack[X],dfn[X],low[X];
int bcnt,top,depth,n,m,qq;
int head[X];
int col[X],ind[X],con[X];
bool map[X][X];
bool instack[X];

struct node
{
    int y,next;
}p[X];

void dfs(int u)
{
    instack[u] = true;
    stack[++top] = u;
    low[u] = dfn[u] = ++depth;
    int v;
    for(int i=head[u];i!=-1;i=p[i].next)
    {
        v = p[i].y;
        if(!low[v])
        {
            dfs(v);
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

void tarjan()
{
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    depth = top = bcnt = 0;
    for(int i=0;i<(n<<1);i++)
        if(!low[i])
            dfs(i);
}

void build_dag()
{
    int y;
    for(int i=0;i<(n<<1);i++)
        for(int j=head[i];j!=-1;j=p[j].next)
        {
            y = p[j].y;
            if(father[i]!=father[y])
                map[father[y]][father[i]] = true;
        }
    for(int i=1;i<=bcnt;i++)
        for(int j=1;j<=bcnt;j++)
            if(map[i][j])
                ind[j]++;
}

void topsort()
{
    for(int i=1;i<=bcnt;i++)
        if(ind[i]==0)
            stack[++top] = i;
    int x;
    while(top)
    {
        x = stack[top--];
        if(!col[x])
        {
            col[x] = 1;
            col[con[x]] = 2;
        }
        for(int i=1;i<=bcnt;i++)
            if(map[x][i])
            {
                if(--ind[i]==0)
                    stack[++top] = i;
            }
    }
}

void solve()
{
    for(int i=0;i<n;i++)
    {
        if(father[i<<1]==father[i<<1|1])
        {
            puts("bad luck");
            return;
        }
        con[father[i<<1]] = father[i<<1|1];
        con[father[i<<1|1]] = father[i<<1];
    }

    memset(map,false,sizeof(map));
    memset(ind,0,sizeof(ind));
    build_dag();

    memset(col,0,sizeof(col));
    top = 0;
    topsort();

    for(int i=2;i<(n<<1);i+=2)
    {
        if(i!=2)
            printf(" ");
        if(col[father[i]]==col[father[0]])
            printf("%dw",i>>1);
        else
            printf("%dh",i>>1);
    }
    cout<<endl;
}

void add(int x,int y)
{
    p[qq].y = y;
    p[qq].next = head[x];
    head[x] = qq++;
}

void input()
{
    qq = 0;
    memset(head,-1,sizeof(head));

    char s,str;
    int x,y,xx,yy;
    while(m--)
    {
        scanf("%d%c %d%c",&x,&s,&y,&str);
        if(s=='h')
        {
            xx = x<<1;  //Ů�ı��Ϊ0,2,4...
            x = x<<1|1; //�еı��Ϊ1,3,5...
        }
        else
        {
            xx = x<<1|1;
            x = x<<1;
        }
        if(str=='h')
        {
            yy = y<<1;
            y = y<<1|1;
        }
        else
        {
            yy = y<<1|1;
            y = y<<1;
        }
        add(x,yy);
        add(y,xx);
    }
    add(0,1);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m)
    {
        input();
        tarjan();
        solve();
    }
    return 0;
}
