/*

题目:
    多源多汇问题，给出np个电站的信息（每间电站的最大电力供给量以及标号），
    给出nc个用户（给出他们各自的节点标号以及需要的电力量），给出m段电网
    （给出起始终止的标号以及最大电量供给量）。现在问用户最多能够得到的电力

分析：
    多源多汇问题，增加一个超级源点以及增加一个超级源点，另外若用连接矩阵做
    的话，需要把超级源点的供给量相加或者直接赋为inf即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1005;
const int maxm = 100005;
const int inf = 1e8;
#define debug puts("here");

int head[maxn],arc[maxn],pre[maxn],gpa[maxn],cur[maxn],dis[maxn];
int n,m,s,t,cl,np,nc;

struct node
{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f)
{
    edge[++cl].y = y;
    edge[cl].next = head[x];
    edge[cl].f = f;
    head[x] = cl;

    edge[++cl].y = x;
    edge[cl].f = 0;
    edge[cl].next = head[y];
    head[y] = cl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>np>>nc>>m)
    {
        memset(head,0,sizeof(head));
        cl = 1;
        s = n+1;
        t = n+2;
        n += 2;

        for(int i=0;i<m;i++)
        {
            while(getchar()!='(');

            scanf("%d,%d",&x,&y);
            getchar();
            scanf("%d",&z);
            add(x,y,z);
        }
        for(int i=0;i<np;i++)
        {
            while(getchar()!='(');

            scanf("%d",&x);
            getchar();
            scanf("%d",&y);
            add(s,x,y);
        }
        for(int i=0;i<nc;i++)
        {
            while(getchar()!='(');

            scanf("%d",&x);
            getchar();
            scanf("%d",&y);
            add(x,t,y);
        }

        memset(dis,0,sizeof(dis));
        memset(gpa,0,sizeof(gpa));
        gpa[0] = n;
        for(int i=1;i<n;i++)
            arc[i] = head[i];
        int i = s;
        int MIN;
        int aug = inf;
        int flow = 0;
        bool ok;



        while(dis[s]<n)
        {
            ok = false;
            cur[i] = aug;
            for(int j=arc[i];j;j=edge[j].next)
                if(edge[j].f>0&&dis[edge[j].y]+1==dis[i])
                {
                    ok = true;
                    arc[i] = j;
                    aug = min(aug,edge[j].f);
                    pre[edge[j].y] = j;
                    i = edge[j].y;
                    if(i==t)
                    {
                        flow += aug;
                        while(i!=s)
                        {
                            edge[pre[i]].f -= aug;
                            edge[pre[i]^1].f += aug;
                            i = edge[pre[i]^1].y;
                        }
                        aug = inf;
                    }
                    break;
                }
            if(ok)
                continue;
            MIN = n-1;
            for(int j=head[i];j;j=edge[j].next)
                if(edge[j].f>0&&dis[edge[j].y]<MIN)
                {
                    arc[i] = j;
                    MIN = dis[edge[j].y];
                }
            if(--gpa[dis[i]]==0)
                break;
            dis[i] = MIN+1;
			++gpa[dis[i]];
            if(i!=s)
            {
                i = edge[pre[i]^1].y;
                aug = cur[i];
            }
        }
        cout<<flow<<endl;
    }
    return 0;
}
