/*

题目：
    给你n个整数（都处于区间[-500000,500000]），请按从大到小的顺序输出其中前m大的数。

分析：
    直接利用数组use[i+500000]表示数字i的出现次数，然后再输出即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000002;
const int T = 500000;

int n,m;
int use[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        int x;
        memset(use,0,sizeof(use));
        for(int i=0;i<n;i++)
        {
            scanf("%d",&x);
            use[x+T]++;
        }
        bool ok = false;
        for(int i=X-2;i>=0&&m;i--)
            while(use[i]&&m)
            {
                m--;
                if(ok)
                    printf(" ");
                else
                    ok = true;
                printf("%d",i-T);
                use[i]--;
            }
        cout<<endl;
    }
    return 0;
}
