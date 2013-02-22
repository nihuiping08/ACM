#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 5005;

int n,m,p,f[X];

int find_set(int x)
{
    if(x!=f[x])
        f[x] = find_set(f[x]);
    return f[x];
}

int main()
{
    freopen("sum.in","r",stdin);
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++)
        f[i] = i;
    int x,y;
    while(m--)
    {
        scanf("%d%d",&x,&y);
        x = find_set(x);
        y = find_set(y);
        if(x!=y)
            f[y] = x;
    }
    while(p--)
    {
        scanf("%d%d",&x,&y);
        x = find_set(x);
        y = find_set(y);
        if(x!=y)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
