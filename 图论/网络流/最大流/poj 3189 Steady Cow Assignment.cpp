/*

题目：
    要求最小的区间，使得满足所有奶牛都能够安置下来

分析：
    直接枚举或二分枚举答案+最大流

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 25;
const int maxn = 1050;
const int maxm = 200005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t,d;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];
int a[maxn][X],fav[X];

struct node{
    int y,f,next;
}edge[maxm];

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

int sap(){
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = t;
    for(int i=1;i<=t;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<t){
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
        MIN = t-1;
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
    return ans;
}

bool build(int x,int y){
    memset(po,0,sizeof(po));
    tol = 1;
    s = n+m+1;
    t = s+1;
    //cout<<x<<" "<<y<<endl;
    for(int i=1;i<=n;i++)
        for(int j=x;j<=y;j++)
            add(i,a[i][j]+n,1);
    for(int i=1;i<=n;i++)
        add(s,i,1);
    for(int j=1;j<=m;j++)
        add(j+n,t,fav[j]);
    int sum = sap();
    if(sum<n)
        return false;
    cout<<y-x+1<<endl;
    return true;
}

void solve(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-i+1;j++)
            if(build(j,i+j-1))
                return;
}

void input(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=m;i++)
        scanf("%d",&fav[i]);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        input();
        solve();
    }
    return 0;
}
