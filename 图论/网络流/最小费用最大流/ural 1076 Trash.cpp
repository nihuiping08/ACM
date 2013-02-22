/*

��Ŀ��
    ��Ŀ�����Ǹ���N������Ͱ��ÿ������Ͱ��װ��N��������ͬ�������������
    �������࣬Ҫ��ÿ������Ͱװһ���������ƶ�һ����λ����������1�Ĵ��ۣ�
    ����С���ƶ����ۣ�ʹ������������ࡣ

������
    ���������Թ���������ͼ�����ƥ���ģ�͡���ԭ�е�����Ͱ����X����
    �еĶ��㣬�������࿴��Y�����еĶ��㣬��(a,b)��ʾa����Ͱװb��������
    �����ƶ��Ĵ��ۡ������ͼ����СȨ�걸ƥ�䣬ƥ���Ȩֵ֮����Сֵ��
    ��Ҫ��Ľ����
    Ϊ���ܹ�ʹ�������Ȩƥ���KM�㷨��ֻ������бߵ�Ȩֵȡ�෴��������
    ��Ȩƥ�䣬�����ȡ�෴�����ɡ�

    �����������С������������㷨��������X������һ��Դ�㣬����ÿ���ߵ�
    ����Ϊ1������Ϊ0������Y��ͬ������һ����㣬ÿ������ߵ�����Ϊ1������
    Ϊ0��ԭͼ�еıߵ�������Ϊ1�����þ�Ϊԭ�����෴�����������С���ü���
    �ܵ�Ȩֵ

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 1005;
const int maxm = 100005;
const int inf = 1e8;
#define debug puts("here");

int po[maxn],pre[maxn],dis[maxn];
bool use[maxn];
int head,tail,q[maxm];
int n,m,s,t,cl,ans;

struct node
{
    int y,f,c,next;
}edge[maxm];

void add(int x,int y,int f,int c)
{
    edge[++cl].y = y;
    edge[cl].f = f;
    edge[cl].c = c;
    edge[cl].next = po[x];
    po[x] = cl;

    edge[++cl].y = x;
    edge[cl].c = -c;
    edge[cl].f = 0;
    edge[cl].next = po[y];
    po[y] = cl;
}

int spfa()
{
    memset(use,false,sizeof(use));
    for(int i=0;i<=n;i++)
        dis[i] = inf;
    head = tail = 0;
    q[tail++] = s;
    dis[s] = 0;
    pre[s] = 0;
    int x,y;
    while(head<tail)
    {
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next)
        {
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y])
            {
                dis[y] = edge[i].c+dis[x];
                pre[y] = i;
                if(!use[y])
                {
                    q[tail++] = y;
                    use[y] = true;
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    int aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y])
    {
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x;
    while(cin>>n)
    {
        m = n;
        n = n*2+2;
        s = m<<1|1;
        t = s+1;
        cl = 1;
        int sum = 0;
        memset(po,0,sizeof(po));

        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&x);
                sum += x;
                add(i,j+m,1,-x);
            }
        for(int i=1;i<=m;i++)
            add(s,i,1,0);
        for(int j=1;j<=m;j++)
            add(j+m,t,1,0);

        ans = 0;
        while(spfa());

        cout<<sum+ans<<endl;
    }
    return 0;
}
