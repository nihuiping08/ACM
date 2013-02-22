#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define X 205
const int INF = 100000000;
string ma[X];
int map[X][X],dis[X],n,cnt,ans;
int use[X];
void dijkstra(int s)
{
    memset(dis,0,sizeof(dis));
    memset(use,false,sizeof(use));
    int k,MAX;
    dis[s] = INF;
    for(int i=1;i<=n;i++)
    {
        MAX = -1;
        for(int j=1;j<=n;j++)
            if(!use[j]&&MAX<dis[j])
                MAX = dis[k=j];
        use[k] = true;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]<min(dis[k],map[k][j]))
                dis[j] = min(dis[k],map[k][j]);
    }
}
int insert(string s)
{
    for(int i=1;i<=cnt;i++)
        if(ma[i]==s)
            return i;
    ma[++cnt] = s;
    return cnt;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int m,dist,x,y,ret = 0;
    string s,e;
    while(scanf("%d%d",&n,&m),n||m)
    {
        cnt = 0;
        ans = INF;
        memset(map,0,sizeof(map));
        while(m--)
        {
            cin>>s>>e>>dist;
            x = insert(s);
            y = insert(e);
            map[x][y] = map[y][x] = dist;
        }
        cin>>s>>e;
        x = insert(s);
        y = insert(e);
        dijkstra(x);
        printf("Scenario #%d\n",++ret);
        cout<<dis[y]<<" tons"<<endl<<endl;
    }
    return 0;
}
