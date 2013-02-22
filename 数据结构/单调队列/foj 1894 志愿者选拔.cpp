/*

题目：
    询问队列中的最大值，队列的头部可以删除

分析：
    利用单调序列记录当前的最大数，比如如下序列：
    3 1 5 7 6 4
    首先：
    3
    3 1
    3 1 5   》 5
    5       》 7
    7 6
    7 6 4
    每次得要从队尾向队首删除比当前的数要小的数，直到队列为空或者遇到了比他大的数为止。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1000005;
#define debug puts("here");

struct node
{
    int data,id;
}q[X];

int head,tail,top,cnt;
char s[10],p[10];

int main()
{
    freopen("sum.in","r",stdin);
    int ncase,x,i,j;
    cin>>ncase;
    while(ncase--)
    {
        scanf("%s",s);
        top = cnt = head = tail = 0;
        i = j = 0;
        while(scanf("%s",s),s[0]!='E')
        {
            if(s[0]=='C')
            {
                scanf("%s%d",s,&x);
                while(tail<head&&q[head].data<x)
                    head--;
                q[++head].data = x;
                q[head].id = ++i;
            }
            else if(s[0]=='G')
            {
                j++;
                while(tail<head&&q[tail+1].id<=j)
                    tail++;
            }
            else
            {
                if(tail<head)
                    printf("%d\n",q[tail+1].data);
                else
                    printf("-1\n");
            }
        }
    }
    return 0;
}
