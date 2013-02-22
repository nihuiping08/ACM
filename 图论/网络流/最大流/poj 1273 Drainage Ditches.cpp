/*

��Ŀ��
    ��n���Ƚϵ͵�ˮ�ӣ�����m��ˮ������ʼ����ֹ�����������������������Ƕ���

������
    ��Ŀ�������������رߣ���������SAP�㷨�������ڽӱ��Ļ���̫Ӱ�죬ֱ�ӽ�ͼ
    Ȼ��������������ɣ�˳�㽨���Լ���ģ��

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 2005;
const int maxm = 20005;
const int inf = 1e8;

int arc[maxn],cur[maxn],gpa[maxn],head[maxn],dis[maxn],pre[maxn];
int cl,n,m,s,t;

struct node
{
    int y,next,f;
}edge[maxm];

void add(int x,int y,int f)
{
    edge[++cl].y = y;
    edge[cl].f = f;
    edge[cl].next = head[x];
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
    while(cin>>m>>n)
    {
        s = 1;
        t = n;
        cl = 1;
        memset(head,0,sizeof(head));

        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
        }

        memset(gpa,0,sizeof(gpa));
        memset(dis,0,sizeof(dis));

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
