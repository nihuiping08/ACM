/*

有重边，WA了6次

很裸的最短路问题。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1005;
const int INF = 1000000000;

int map[X][X],dis[X],n,t;
bool use[X];

void dijkstra(){
    for(int i=1;i<=n;i++)
        dis[i] = map[i][1];
    memset(use,false,sizeof(use));
    dis[1] = 0;
    int k,MIN;
    use[1] = true;
    for(int i=1;i<n;i++){
        MIN = INF;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[k = j];
        use[k] = true;
        for(int j=1;j<=n;j++)
            if(!use[j])
                dis[j] = min(dis[j],dis[k]+map[k][j]);
    }
    cout<<dis[n]<<endl;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,z;
    cin>>t>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            map[i][j] = INF;
    for(int i=0;i<t;i++){
        scanf("%d%d%d",&x,&y,&z);
        map[x][y] = map[y][x] = min(z,map[x][y]);
    }
    dijkstra();

    return 0;
}
