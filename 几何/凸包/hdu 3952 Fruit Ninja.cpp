/*

题目：
    给出n个凸包，现在要用一条直线切这些凸包，问最多能够切多少个

分析：
    水题，但是不知道哪里错了，后来用另一种方法过了。
    由于数据小，直接枚举所有的点，然后判断线段是否相交即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 102;

int a[X],n;

struct node
{
    int x,y;
}p[X][X],d[1005];

int det(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool bet(node a,node b,node o)
{
    int temp = (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
    if(temp<=0)
        return true;
    return false;
}

bool segment(node a,node b,node c,node d)
{
    int d1 = det(a,b,c);
    int d2 = det(a,b,d);
    int d3 = det(c,d,a);
    int d4 = det(c,d,b);
    if(d1*d2<0&&d3*d4<0)
        return true;
    else if(d1==0&&bet(a,b,c))
        return true;
    else if(d2==0&&bet(a,b,d))
        return true;
    else if(d3==0&&bet(c,d,a))
        return true;
    else if(d4==0&&bet(c,d,b))
        return true;
    else
        return false;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    int qq = 0;
    while(ncase--)
    {
        scanf("%d",&n);
        int sum = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            for(int j=0;j<a[i];j++)
            {
                scanf("%d%d",&p[i][j].x,&p[i][j].y);
                d[sum++] = p[i][j];
            }
        }
        if(n==1)
        {
            printf("Case %d: %d\n",++qq,1);
            continue;
        }
        int ans = 0;
        int temp;
        for(int i=0;i<sum;i++)
            for(int j=i+1;j<sum;j++)
            {
                temp = 0;
                for(int k=0;k<n;k++)
                    for(int l=0;l<a[k]-1;l++)
                        if(segment(d[i],d[j],p[k][l],p[k][l+1]))
                        {
                            temp++;
                            break;
                        }
                ans = max(ans,temp);
            }
        printf("Case %d: %d\n",++qq,ans);
    }
    return 0;
}
