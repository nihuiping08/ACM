/*

��Ŀ��
    Ѱ��ѭ���ڲ����ѭ���ڵĳ���

������
    ֻ�����n���г�10��mȡ������Ȼ���ж������Ƿ����ؼ���


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
