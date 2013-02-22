/*

题目：
    求最上面的木根序号

分析：
    直接枚举加判断线段是否相交

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int X = 100005;
#define esp 1e-8

bool use[X];
int n;

struct node
{
    double x,y;
}p[2][X];

int dcmp(double x)
{
    if(abs(x)<esp)
        return 0;
    return x>0?1:-1;
}

double det(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool bet(node a,node b,node o)
{
    if(o.x>=min(a.x,b.x)&&o.x<=max(a.x,b.x))
        return true;
    return false;
}

bool segment(node a,node b,node c,node d)
{
    int d1 = dcmp(det(a,b,c));
    int d2 = dcmp(det(a,b,d));
    int d3 = dcmp(det(c,d,a));
    int d4 = dcmp(det(c,d,b));
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
    freopen("sum.out","w",stdout);
    while(cin>>n,n)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<2;j++)
                scanf("%lf%lf",&p[j][i].x,&p[j][i].y);
        memset(use,false,sizeof(use));
        for(int i=0;i<n;i++)
        {
            if(use[i])
                continue;
            for(int j=i+1;j<n;j++)
                if(segment(p[0][i],p[1][i],p[0][j],p[1][j]))
                {
                    use[i] = true;
                    break;
                }
        }
        printf("Top sticks:");
        bool ok = false;
        for(int i=0;i<n;i++)
        {
            if(!use[i])
            {
                if(ok)
                    printf(",");
                else
                    ok = true;
                printf(" %d",i+1);
            }
        }
        printf(".\n");
    }
    return 0;
}
