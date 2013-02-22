/*

��Ŀ��
    ��m����Ȧ��ÿ����Ȧ�������Ϊpig[i]��������n�������ÿ�������ʱ���
    ��Ȧ���ţ�ƽʱ�������ģ���Ȼ��ÿ�������ӵ�е�Կ���Լ����Ǹ��ԵĹ�������
    ������ÿ������󣬵�ǰ�򿪵���Ȧ����ֻ�з��������ڵ���Ȧλ�ã����������
    �����ţ���������ΰ���ʹ������ȥ���������������

������
        ��ֱ�Ӱ���Ȧ����Դ�㣬����Ϊ����Ȧ����Ŀ��ÿλ����ܹ��������Ȧ����
    ��֮ǰ����Ȧ�����򿪹��Ļ�������һ��򿪵���Ȧ��������ߣ����鼯��������
    ���ÿλ������ϻ�㣬����Ϊ��Ϊ��ҵĹ������ޡ�
        ��������������Ļ���ͼ��������Ϊk*m���ܴ����Ե�Ҫ�Ż���ͼ��
        ����ע�⵽����ÿλ��ҹ���ĸ���Ȧ���֮ǰ����Ҵ򿪹�����ô����Ϊ�����
    ��һλ��ҹ�ͬ������ͬһ����Ȧ����ֻ����ҽ�����ϵ�����ߵ���Ŀ�����١�
        ��β��������ȣ��Ե�һλ�򿪸���Ȧ��������ϻ�㣬����Ϊ����Ȧ�����Ŀ��
    �����������������Ļ��������߽�����ϵ������ǰһλ�򿪹�����Ȧ����ң����
    �����߶εļ�ͷ��ǰ��ָ��ǰ����ң���������Ϊ00�����ڿ���ǰһλ�����ʣ��
    �ܶ࣬����������Ҳ�֪����Ҳ����֪��������󣬶������������һ�������߶�ָ��
    ��㣬����������Ϊ���Ĺ������޼���

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
