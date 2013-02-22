#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 1005;

bool use[X];
int n,m;
int p[X];

int find_set(int x)
{
    if(x!=p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void union_set(int x,int y)
{
    x = find_set(x);
    y = find_set(y);
    if(x!=y)
        p[y] = x;
}

int main()
{
    //freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        p[i] = i;
    memset(use,false,sizeof(use));
    int x,y;
    while(n--)
    {
        scanf("%d%d",&x,&y);
        union_set(x,y);
    }
    int ans = 0;
    for(int i=1;i<=m;i++)
    {
        x = find_set(i);
        if(!use[x])
        {
            ans++;
            use[x] = true;
        }
    }
    cout<<ans<<endl;
    return 0;
}
