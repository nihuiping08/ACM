/*

题目：
    有m个猪圈，每间猪圈猪的数量为pig[i]，现在有n个买家猪，每次买猪的时候打开
    猪圈的门（平时是上锁的）。然后每个买家所拥有的钥匙以及他们各自的购买上限
    给出，每次买完后，当前打开的猪圈可以只有分配猪所在的猪圈位置，分配完后再
    关上门，现在问如何安排使得卖出去的猪的数量是最多的

分析：
        若直接把猪圈连上源点，流量为该猪圈的数目，每位买家能够购买的猪圈（以
    及之前该猪圈若被打开过的话，与他一起打开的猪圈多得连上线（并查集）），最
    后对每位买家连上汇点，流量为改为买家的购买上限。
        但是如果这样做的话，图的最大边数为k*m，很大，所以得要优化建图。
        我们注意到，若每位买家购买的该猪圈编号之前有买家打开过，那么，改为买家与
    上一位买家共同购买了同一个猪圈，若只对买家建立关系，连线的数目大大减少。
        如何操作？首先，对第一位打开该猪圈的买家连上汇点，流量为该猪圈猪的数目，
    若后面有买家来购买的话，对两者建立关系，连上前一位打开过该猪圈的买家，这段
    有向线段的箭头由前面指向当前的买家，流量可设为00（由于可能前一位买家买剩了
    很多，这个我们暂且不知道，也不必知道）。最后，对所有买家连上一条有向线段指向
    汇点，流量上线设为他的购买上限即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1005;
const int maxm = maxn*maxn*2;
const int inf = 1e8;
#define debug puts("here");

int arc[maxn],cur[maxn],po[maxn],dis[maxn],gpa[maxn],pre[maxn];
int n,m,s,t,cl;
int a[maxn][maxn],num[maxm],pig[maxn],buy[maxm];

struct node
{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f)
{
    ++cl;
    edge[cl].y = y;
    edge[cl].f = f;
    edge[cl].next = po[x];
    po[x] = cl;

    ++cl;
    edge[cl].y = x;
    edge[cl].f = 0;
    edge[cl].next = po[y];
    po[y] = cl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,k;
    while(cin>>m>>n)
    {
        s = n+1;
        t = n+2;
        cl = 1;
        memset(po,0,sizeof(po));
        memset(num,0,sizeof(num));

        for(int i=1;i<=m;i++)
            scanf("%d",&pig[i]);

        for(int i=1;i<=n;i++)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&x);
                a[x][num[x]++] = i;
            }
            scanf("%d",&buy[i]);
        }

        for(int i=1;i<=n;i++)
            add(i,t,buy[i]);
        for(int i=1;i<=m;i++)
        {
            if(num[i]>0)
                add(s,a[i][0],pig[i]);
            for(int j=1;j<num[i];j++)
                add(a[i][j-1],a[i][j],inf);
        }

        n += 2;

        memset(gpa,0,sizeof(gpa));
        memset(dis,0,sizeof(dis));

        gpa[0] = n;
        for(int i=1;i<=n;i++)
            arc[i] = po[i];

        int i = s;
        int MIN;
        int aug = inf;
        int flow = 0;
        bool ok;

        while(dis[s]<n)
        {
            cur[i] = aug;
            ok = false;
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
            for(int j=po[i];j;j=edge[j].next)
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
