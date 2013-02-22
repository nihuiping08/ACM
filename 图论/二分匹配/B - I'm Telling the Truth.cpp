/*

ÌâÄ¿£º


*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 100005;
const int maxn = 125;

int n,cl,ym[X],m,mm;
bool use[X];
bool map[61][X];
int a[X],top;


bool dfs(int x)
{
    for(int i=mm;i>=m;i--)
        if(map[x][i]&&!use[i])
        {
            use[i] = true;
            if(ym[i]==-1||dfs(ym[i]))
            {
                ym[i] = x;
                return true;
            }
        }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int i=n;i;i--)
    {
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret++;
    }
    cout<<ret<<endl;
    bool ok = false;
    top = 0;
    for(int i=m;i<=mm;i++)
    {
        if(ym[i]!=-1)
            a[top++] = ym[i];
    }
    sort(a,a+top);
    for(int i=0;i<top;i++)
    {
        ok?printf(" "):ok = true;
        printf("%d",a[i]);
    }
    cout<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        m = 1000000;
        mm = 0;
        scanf("%d",&n);
        int x,y;
        memset(map,false,sizeof(map));

        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            m = min(m,x);
            mm = max(mm,y);
            for(int j=x;j<=y;j++)
                map[i][j] = true;
        }
        hungry();
    }
    return 0;
}
