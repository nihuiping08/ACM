/*

用结构体数组模拟栈，结构体中保存当前min与max的值

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 65537;

int n,top;

struct node
{
    int max,min;
}stack[X];

int main()
{
    freopen("sum.in","r",stdin);
    char s[10];
    int x;
    int ncase = 0;
    while(cin>>n,n)
    {
        printf("Case %d\n",++ncase);
        top = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%s",s);
            if(s[0]=='m')
            {
                if(!top)
                    printf("null\n");
                else
                {
                    if(s[1]=='a')
                        printf("%d\n",stack[top-1].max);
                    else
                        printf("%d\n",stack[top-1].min);
                }
            }
            else
            {
                if(s[1]=='o')
                {
                    if(top)
                        top--;
                }
                else
                {
                    scanf("%d",&x);
                    if(top)
                    {
                        stack[top].max = max(x,stack[top-1].max);
                        stack[top].min = min(x,stack[top-1].min);
                    }
                    else
                        stack[top].min = stack[top].max = x;
                    top++;
                }
            }
        }
    }

    return 0;
}
