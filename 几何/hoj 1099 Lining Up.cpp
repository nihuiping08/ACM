/*

题目：
    给出点集，问在最多有多少点在同一直线上

分析：
    直接枚举所有的点，时间复杂度为O(n^3)，若以每次对枚举的一个点为起点，算出斜率，
    然后排序，再按斜率相同的计数器加一，时间复杂度为O(n^2)

*/
/*
#include <iostream>
#include <cstdio>
using namespace std;
#define X 705
struct point
{
    int x,y;
}p[X];
int n,ret;
void online(point o,point a,point b)
{
    if((a.x-o.x)*(b.y-o.y)==(b.x-o.x)*(a.y-o.y))
        ret++;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n,n)
    {
        for(int i=1;i<=n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        int ans = 0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                ret = 0;
                for(int k=j+1;k<=n;k++)
                    online(p[i],p[j],p[k]);
                ans = max(ans,ret);
            }
        }
        cout<<ans+2<<endl;
    }
    return 0;
}
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#define inf 1e20
using namespace std;
struct point
{
    int x,y;
}p[705];
double k[705];
double cal_k(point b,point a)   //求斜率
{
    if(a.x==b.x)        //如果横坐标相等，斜率无限大
        return inf;
    return (b.y-a.y)*1.0/(b.x-a.x);
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int n;
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        int ans = 0,ret,cnt;
        for(int i=0;i<n;i++)
        {
            cnt = 0;
            for(int j=i+1;j<n;j++)
                k[cnt++] = cal_k(p[i],p[j]);//保存斜率
            sort(k,k+cnt);  //对斜率进行排序
            ret = 1;
            for(int j=1;j<cnt;j++)  //枚举斜率是否相等（由于有相同起点，斜率相等即为三点共线）
            {
                if(k[j]==k[j-1])
                    ret++;
                else
                {
                    ans = max(ans,ret);
                    ret = 1;
                }
            }
            ans = max(ans,ret);
        }
        printf("%d\n",ans+1);
    }

    return 0;
}
