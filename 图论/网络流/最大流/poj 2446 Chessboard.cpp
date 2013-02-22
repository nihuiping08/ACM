/*

题目：
    用两节木棍对有挖空的棋盘进行覆盖的问题，问是否有解

分析：
    对棋盘进行染色，然后对白色的连上源点，对黑色的连上汇点（都是没有挖
    空的），然后对相邻的黑格（若都没被挖空）连上线，流量均为1即可建图

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 35;
const int maxn = 1200;
const int maxm = 100005;
const int inf = 1e9;
//#define debug puts("here");

struct node{
    int y,f,next;
}edge[maxm];

int arc[maxn],gap[maxn],dis[maxn],pre[maxn],cf[maxn];
int po[maxn],tol;
int qq,n,m,s,t;
bool use[X][X],map[X][X];

int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void add(int x,int y,int f){
    edge[++tol].f = f;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].f = 0;
    edge[tol].y = x;
    edge[tol].next = po[y];
    po[y] = tol;
}

void sap(){
    n = t;
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = n;
    for(int i=1;i<=n;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<n){
        ok = false;
        cf[i] = aug;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    ans += aug;
                    while(i!=s){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                        i = edge[pre[i]^1].y;
                    }
                    aug = inf;
                }
                break;
            }
        if(ok)
            continue;
        MIN = n-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]]++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
    qq >>= 1;
    qq==ans?puts("YES"):puts("NO");
}

bool build(){
    memset(po,0,sizeof(po));
    tol = 1;

    memset(use,0,sizeof(use));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((j-i)&1)
                use[i][j] = 1;
    int x,y,dx,dy;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(use[i][j]||map[i][j])
                continue;
            x = i*m-m+j;
            for(int k=0;k<4;k++){
                dx = i+dir[k][0];
                dy = j+dir[k][1];
                if(dx<1||dy<1||dx>n||dy>m||map[dx][dy])
                    continue;
                y = dx*m-m+dy;
                //cout<<x<<" "<<y<<endl;
                add(x,y,1);
            }
        }
    s = m*n+1;
    t = s+1;
    x = y = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(map[i][j])
                continue;
            if(use[i][j]){
                add(i*m-m+j,t,1);
                x++;
            }
            else{
                add(s,i*m-m+j,1);
                y++;
            }
        }
    n = t;
    return x==y;
}

int main(){
    freopen("a.in","r",stdin);
    int x,y,k;
    while(cin>>n>>m>>k){
        qq = n*m-k;
        memset(map,false,sizeof(map));
        for(int i=0;i<k;i++){
            scanf("%d%d",&x,&y);
            map[y][x] = true;
        }
        if(((n*m-k)&1)||!build()){
            puts("NO");
            continue;
        }
        sap();
    }

    return 0;
}
