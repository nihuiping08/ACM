/*

题目：
    奶牛去参加舞会，由于路都是单向的，奶牛们很懒，所以都是选择最短的距离去
    参加舞会和从舞会地点回家，现在问你走的距离最远的奶牛需要走的最短距离

分析：
    从舞会地点回家的最短距离好求，直接spfa搞定，但是每个奶牛从她们各自的家
    出发到达舞会地点用floyd很容易算出，但是时间复杂度不允许！
    逆向思维！在建一个逆向的图，然后再求从舞会地点到各点的距离，最后求和的
    最大值即可！

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1005;
const int inf = 1e9;
const int maxn = 1e5+10;
#define debug puts("here");

int ah[X],bh[X];
int n,m,src;
bool use[X];
int dis[2][X];
int q[maxn],h,t;

struct node
{
    int y,w,next;
}a[maxn],b[maxn];

void spfa(node *p,int *head,int id)
{
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[id][i] = inf;
    dis[id][src] = 0;
    use[src] = true;
    h = t = 0;
    q[t++] = src;
    int x,y,w;
    while(h<t)
    {
        x = q[h++];
        use[x] = false;
        for(int i=head[x];i!=-1;i=p[i].next)
        {
            y = p[i].y;
            w = p[i].w+dis[id][x];
            if(w<dis[id][y])
            {
                dis[id][y] = w;
                if(!use[y])
                {
                    use[y] = true;
                    q[t++] = y;
                }
            }
        }
    }
}

void a_add(int x,int y,int w,int i)
{
    a[i].y = y;
    a[i].w = w;
    a[i].next = ah[x];
    ah[x] = i;
}

void b_add(int x,int y,int w,int i)
{
    b[i].y = y;
    b[i].w = w;
    b[i].next = bh[x];
    bh[x] = i;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>m>>src)
    {
        memset(ah,-1,sizeof(ah));
        memset(bh,-1,sizeof(bh));
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            a_add(x,y,z,i);
            b_add(y,x,z,i);
        }
        spfa(a,ah,0);
        spfa(b,bh,1);
        int ans = 0;
        for(int i=1;i<=n;i++)
            ans = max(ans,dis[0][i]+dis[1][i]);
        cout<<ans<<endl;
    }
    return 0;
}
