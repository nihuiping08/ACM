/*

题目：
    寻找循环节并输出循环节的长度

分析：
    只需对数n进行乘10除m取余数，然后判断余数是否有重即可


*/
#include <cstdio>
#include <cstring>

const int X = 1005;

int use[X];
int n,m;

void solve()
{
    int temp,r = n,i = 1;
    use[n] = 0;
    putchar('.');
    while(true)
    {
        r *= 10;
        temp = r/m;
        r %= m;
        if(i%50==0)
            puts("");
        printf("%d",temp);
        if(use[r]==-1)
            use[r] = i;
        else
        {
            printf("\nThe last %d digits repeat forever.\n",i-use[r]);
            return;
        }
        if(!r)
        {
            puts("");
            puts("This expansion terminates.");
            return;
        }
        i++;
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d%d",&n,&m),n||m)
    {
        memset(use,-1,sizeof(use));
        solve();
    }

    return 0;
}
