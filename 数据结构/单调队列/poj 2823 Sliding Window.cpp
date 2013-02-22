/*

题目：
    给出n个数，现在问你k个连续的数的最值

分析:
    求最大值时，维护一个下降的单调队列，求最小值时，维护一个上升序列即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;
#define debug puts("here");

int a[X],b[X],in[X],n,k,dp[X];

struct node
{
    int id;
    int a;
}p[X];

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n>>k)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&in[i]);
        int head = 1,tail = 0;
        p[0].id = 0;
        p[0].a = a[0] = b[0] = in[0];
        for(int i=1;i<n;i++)
        {
            while(tail<head&&p[tail].id+k<=i)
                tail++;
            while(head>tail&&p[head-1].a<=in[i])
                head--;
            p[head].id = i;
            p[head++].a = in[i];
            a[i] = p[tail].a;
        }

        head = 1;
        tail = 0;
        p[0].id = 0;
        p[0].a = a[0] = b[0] = in[0];
        for(int i=1;i<n;i++)
        {
            while(head>tail&&p[tail].id+k<=i)
                tail++;
            while(head>tail&&p[head-1].a>=in[i])
                head--;
            p[head].id = i;
            p[head++].a = in[i];
            b[i] = p[tail].a;
        }

        printf("%d",b[k-1]);
        for(int i=k;i<n;i++)
            printf(" %d",b[i]);
        puts("");
        printf("%d",a[k-1]);
        for(int i=k;i<n;i++)
            printf(" %d",a[i]);
        puts("");
    }
    return 0;
}
