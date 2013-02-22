/*

题目：
    找出n个点中距离最远的两个，水题

分析:
    由于题目的数据比较小，直接枚举即可，当然还可以直接求凸包加上旋转卡壳算法做

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 6005;

int n;

struct node
{
    double x,y;
}p[X];

double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        double ans = 0,temp;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                temp = dis(p[i].x-p[j].x,p[i].y-p[j].y);
                if(temp>ans)
                    ans = temp;
            }
        printf("%.2lf\n",ans);
    }
    return 0;
}
