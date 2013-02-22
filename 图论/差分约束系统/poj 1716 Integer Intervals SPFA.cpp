/*

������dist[i]��ʾ�ӵ�0����i-1�������Ĺؼ������Ŀ��
�������ݼ���ת��Ϊ��dist[b+1]-dist[a]>=2      =>    dist[a]-dist[b+1]<=-2
����ʵ�������������Լ��������
dist[i+1]-dist[i]<=1
dist[i+1]-dist[i]>=0    =>   dist[i]-dist[i]+1<=0
���ǿ��Խ�ͼ��SPFA��
������dist[max]-dist[min]���ɣ�max��min Ϊ�������ݳ��ֵ��������С�㣩

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;
const int inf = 1e9;
#define debug puts("here");

int dis[X],n,sx,ex;
bool use[X];
int head[X],e;
int q[X*10];

struct node
{
    int y,w;
    int next;
}p[X];

void spfa(int s)
{
    for(int i=0;i<=ex;i++)
        dis[i] = inf;
    memset(use,false,sizeof(use));
    int x,y;
    int h = 0,t = 1;
    dis[s] = 0;
    use[s] = true;
    q[0] = s;
    while(h<t)
    {
        x = q[h++];
        use[x] = false;
        for(int i=head[x];i!=-1;i=p[i].next)
        {
            y = p[i].y;
            if(dis[y]>dis[x]+p[i].w)
            {
                dis[y] = dis[x]+p[i].w;
                if(!use[y])
                {
                    use[y] = true;
                    q[t++] = y;
                }
            }
        }
    }
    printf("%d\n",dis[ex]-dis[sx]);
}

void add(int x,int y,int w)
{
    p[e].y = y;
    p[e].w = w;
    p[e].next = head[x];
    head[x] = e++;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        memset(head,-1,sizeof(head));
        int x,y;
        sx = inf;
	e = 0;
        ex = -inf;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            y++;
            add(y,x,-2);
            sx = min(sx,x);
            ex = max(ex,y);
        }
        for(int i=0;i<ex;i++)
        {
            add(i,i+1,1);
            add(i+1,i,0);
        }
        spfa(ex);
    }
    return 0;
}
