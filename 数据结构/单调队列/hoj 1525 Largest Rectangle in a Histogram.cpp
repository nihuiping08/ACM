/*

题目：
    在坐标轴上给出n个矩形的高，并且每个矩形的宽是单位一，现可用这些矩形组成一个新的矩形，
    求能够组成矩形的最大面积

分析:
    利用单调队列，维护以每一个矩形为高的情况下，向前、向后能够到达的距离。然后再枚举每个
    矩形，计算它们的面积，更新答案。
    维护单调队列的话，我是用结构体存储一个pos（记录最早能够找到比他小数），另外一个就是
    data(记录的是该位的数)。
    比如样例：
    7 2 1 4 5 1 3 3
    首先，队列的进出情况如下：
    data  7   \\  2(发现7大于2,7出队,2的pos可以指向最前的)
    pos  -1   \\  -1

    data  1   \\  1   4（4比1小，由于没有删去队列中元素，4的pos是他自己的位置下标减一）
    pos   -1  \\  -1  2

    data 1   4 5  \\  1（可以发现，1进队列时，队列中的所有元素都需要出队）
    pos  -1  2 3  \\  -1

    data 1   3      \\  1   3(此3非比3)
    pos  -1  5      \\  -1  5
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;
#define debug puts("here");

int num[X],a[X],b[X],n;

struct node
{
    int pos,data;
}l[X],r[X];

int top;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&num[i]);
        top = 0;
        l[0].data = num[0];
        l[0].pos = -1;
        a[0] = -1;
        int cnt;
        for(int i=1;i<n;i++)
        {
            cnt = top;
            while(top>=0&&l[top].data>=num[i])
                top--;
            if(top==-1)
            {
                l[++top].pos = -1;
                l[top].data = num[i];
            }
            else if(top==cnt)
            {
                l[++top].data = num[i];
                l[top].pos = i-1;
            }
            else
            {
                cnt = top;
                l[++top].pos = l[cnt+1].pos;
                l[top].data = num[i];
            }
            a[i] = l[top].pos;
        }
        top = 0;
        r[top].data = num[n-1];
        r[top].pos = n-1;
        b[n-1] = n-1;
        for(int i=n-2;i>=0;i--)
        {
            cnt = top;
            while(top>=0&&r[top].data>=num[i])
                top--;
            if(top==-1)
            {
                r[++top].pos = n-1;
                r[top].data = num[i];
            }
            else if(top==cnt)
            {
                r[++top].data = num[i];
                r[top].pos = i;
            }
            else
            {
                cnt = top;
                r[++top].pos = r[cnt+1].pos;
                r[top].data = num[i];
            }
            b[i] = r[top].pos;
        }
        long long sum = 0;
        for(int i=0;i<n;i++)
            sum = max(sum,(long long)(b[i]-a[i])*num[i]);
        cout<<sum<<endl;
    }
    return 0;
}
