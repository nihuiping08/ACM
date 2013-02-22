/*

2011�걱��������A��
Qin Shi Huang's National Road System


��Ŀ:
    ��ʼ����Ҫ�޹�·��ʹ����n�����п��Ի����Ŀ����n�����еĶ�ά�����Լ�ÿ����
    �еļ�ֵ���������˿�����Ѱ�����ʼ����������һ����·������Ҫ��ʹ�ñ���A/B���,
    A��ʾ������·���ڵ��������еļ�ֵ��B��ʾ���еĹ�·���ȣ�������������·�ĳ��ȣ���

������
    ��Ҫ�����������AҪ�����ܴ�B������С��ҪʹB������С�Ļ��������������С��
    ������Ȼ��ö������С�������ϵ�ÿ���ߣ�ɾ���ñߺ�õ��������㼯�зֱ��ҵ�����ֵ
    �ĵ㣨���У���Ȼ����´𰸡�ʱ�临�Ӷ�ΪO(n^2)���������������еĵ�ʱ�����ǿ���
    ͨ��dfs��ã�����ʵ���뿴����

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

const int X = 1002;
#define INF 1e12

struct node
{
    int x,y,w;
}p[X];

int n;
double map[X][X];
double dis[X],total,ans;
bool use[X];
int pre[X];     //��¼��i��ǰ���ڵ�

double dist(int x1,int y1,int x2,int y2)    //����
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void prim() //����С������
{
    memset(pre,0,sizeof(pre));
    total = 0;
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = INF;
    dis[1] = 0;
    int k;
    double MIN;
    for(int i=0;i<n;i++)
    {
        MIN = INF;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[k = j];
        use[k] = true;
        total += MIN;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]>map[k][j])
                dis[j] = map[k][j],pre[j] = k;
    }
}

void dfs(int i) //dfs��ͨ�������ĺ�����������ѣ��ҵ�ͬһ���������еĵ�
{
    use[i] = true;
    for(int j=1;j<=n;j++)
        if(!use[j]&&pre[j]==i)
            dfs(j);
}

void solve()
{
    double temp;
    ans = 0;
    int a,b;
    for(int i=1;i<=n;i++)   //ö��ÿ����
    {
        if(pre[i]==0)
            continue;
        temp = total-map[i][pre[i]];    //ɾ����i,pre[i]
        memset(use,false,sizeof(use));
        dfs(i);
        a = b = 0;
        for(int j=1;j<=n;j++)
        {
            if(use[j]&&j!=pre[i])   //��pre[i]ͬһ�����еĵ㣬�ҵ����ļ�ֵ����
                a = max(a,p[j].w);
            else if(!use[j]&&j!=i)    //��iͬһ�����еĵ㡣����
                b = max(b,p[j].w);
        }
        ans = max(ans,(a+b)/temp);
    }
    printf("%.2lf\n",ans);
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].w);
            for(int j=i;j>=1;j--)   //Ԥ��������е����֮��ľ���
                map[i][j] = map[j][i] = dist(p[i].x,p[i].y,p[j].x,p[j].y);
        }
        prim();
        solve();
    }
    return 0;
}
