/*

spfaµÄSTLÖÐµÄqueue°æ

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 10000000;
const int X = 1005;

queue<int> q;
bool use[X];
int map[X][X],dis[X],n,m;

void spfa(int s){
    int x;
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = INF;
    dis[s] = 0;
    use[s] = true;
    q.push(s);
    while(q.size()){
        x = q.front();
        q.pop();
        use[x] = false;
        for(int i=1;i<=n;i++){
            if(dis[i]-map[x][i]>dis[x]){
                dis[i] = map[x][i]+dis[x];
                if(!use[i]){
                    q.push(i);
                    use[i] = true;
                }
            }
        }
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    cin>>m>>n;
    int x,y,z;
    memset(map,127,sizeof(map));
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        if(map[x][y]>z)
            map[x][y] = map[y][x] = z;
    }
    spfa(1);
    cout<<dis[n]<<endl;
    return 0;
}
