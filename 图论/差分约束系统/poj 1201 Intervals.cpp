/*

��Ŀ��
    ��������[ai,bi]������ȫ���Ľ����ĸ���Ϊci����ȫ���������ж��ٸ�Ԫ��

������
    ������dist[i]��ʾ��0��i��ȫ���Ľ����ĸ�����
    �������ݼ���ת��Ϊ��dist[b+1]-dist[a]>=z      =>    dist[a]-dist[b+1]<=-z
    ����ʵ�������������Լ��������
    dist[i+1]-dist[i]<=1
    dist[i+1]-dist[i]>=0    =>   dist[i]-dist[i]+1<=0
    ���ǿ��Խ�ͼ��SPFA��
    ������dist[max]-dist[min]���ɣ�max��min Ϊ�������ݳ��ֵ��������С�㣩

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 50005;
const int inf = 1e9;
#define debug puts("here");

int dis[X],head[X],top,n;
bool use[X];
int mx,mi;

struct node
{
    int y,w,next;
}p[X*3];

void spfa(int src)
{
    memset(use,false,sizeof(use));
    for(int i=0;i<=mx;i++)
        dis[i] = inf;
    queue<int> q;
    use[src] = true;
    dis[src] = 0;
    q.push(src);
    int x,y,w;
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        use[x] = false;
        for(int i=head[x];i!=-1;i=p[i].next)
        {
            y = p[i].y;
            w = p[i].w+dis[x];
            if(dis[y]>w)
            {
                dis[y] = w;
                if(!use[y])
                {
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    printf("%d\n",dis[mx]-dis[mi]);
}

void add(int x,int y,int w)
{
    p[top].y = y;
    p[top].w = w;
    p[top].next = head[x];
    head[x] = top++;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        int x,y,z;
        memset(head,-1,sizeof(head));
        top = 0;
        mx = -inf;
        mi = inf;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            y++;
            add(y,x,-z);
            mi = min(mi,x);
            mx = max(mx,y);
        }
        for(int i=1;i<=mx;i++)
        {
            add(i,i-1,0);
            add(i-1,i,1);
        }
        spfa(mx);
    }
    return 0;
}
