/*

题目：
    给出n个站点，现在每个站点都要派人过去，然后再让那人返回，求所有人从
    站点1出发回到站点1的最小费用

分析：
    逆向建图+正向建图得到的和值即可

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1000005;
const int inf = 1e9;
const int maxn = 1e6+10;
#define debug puts("here");

int ah[X],bh[X];
int n,m,src;
bool use[X];
long long dis[2][X];
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
    int ncase;
    cin>>ncase;
    src = 1;
    while(ncase--)
    {
        cin>>n>>m;
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
        long long ans = 0;
        for(int i=1;i<=n;i++)
            ans += dis[0][i]+dis[1][i];
        cout<<ans<<endl;
    }
    return 0;
}
