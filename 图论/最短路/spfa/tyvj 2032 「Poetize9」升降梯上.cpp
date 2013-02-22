/*

¶þÎ¬spfa¡£¡£¡£

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 22;
const int maxm = 1012;
const int inf = 1e9;

int dis[maxm][maxn],a[maxn],n,m,s;
bool use[maxm][maxn];

struct node{
    int x,y;
    node(){}
    node(int _x,int _y):x(_x),y(_y){}
};

queue<node> q;

int Abs(int x){
    return max(x,-x);
}

void spfa(){
    memset(use,false,sizeof(use));
    memset(dis,0x3f,sizeof(dis));
    dis[1][s] = 0;
    use[1][s] = true;
    while(q.size())
        q.pop();
    q.push(node(1,s));
    while(q.size()){
        node pre = q.front();
        q.pop();
        int x = pre.x;
        int y = pre.y;
        use[x][y] = false;
        for(int i=1;i<=m;i++){
            int dx = x+a[i];
            if(dx<1||dx>n)
                continue;
            int cur = dis[x][y]+2*Abs(a[i])+Abs(i-y);
            if(dis[dx][i]>cur){
                dis[dx][i] = cur;
                if(!use[dx][i]){
                    use[dx][i] = true;
                    q.push(node(dx,i));
                }
            }
        }
    }
    int ans = dis[0][0];
    for(int i=1;i<=m;i++)
        ans = min(dis[n][i],ans);
    ans==dis[0][0]?puts("-1"):printf("%d\n",ans);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=m;i++){
            scanf("%d",&a[i]);
            if(!a[i])
                s = i;
        }
        spfa();
    }
    return 0;
}
