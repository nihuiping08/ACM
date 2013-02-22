/*

��Ŀ��
    ����n�������Լ�m�����󶴵Ķ�ά���꣬ÿֻ����ֻ�ܹ�����һ����������
    ���ٶ��Լ����ܵ�ʱ�䣬�������������ٶ���ֻ����è��

������
    ����ƥ����������Ӽ���������������ƥ������ƥ����

*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 105;

int ym[X],n,m;
double s,v;
bool use[X];
bool map[X][X];

struct node
{
    double x,y;
}a[X],b[X];

bool dfs(int u)
{
    int t;
    for(int v=1;v<=m;v++)
    {
        if(map[u][v]&&!use[v])
        {
            use[v] = true;
            t = ym[v];
            if(t==-1||dfs(t))
            {
                ym[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int u=1;u<=n;u++)
    {
        memset(use,false,sizeof(use));
        if(dfs(u))
            ret++;
    }
    cout<<n-ret<<endl;
}

double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>s>>v)
    {
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        for(int i=1;i<=m;i++)
            scanf("%lf%lf",&b[i].x,&b[i].y);
        memset(map,false,sizeof(map));
        s = s*v;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                double temp = dis(a[i].x-b[j].x,a[i].y-b[j].y);
                if(temp<s)
                    map[i][j] = true;
            }

        hungry();
    }
    return 0;
}
