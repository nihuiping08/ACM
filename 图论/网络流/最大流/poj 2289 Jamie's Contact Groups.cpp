/*

题目：
    给出n个人，以及他们各自可能所在的组，问如何安排人员，使得
    最大的组的人数最小

分析：
    求最大的最小值，二分答案+最大流，对于每个人连上超级源点，
    流量为1，对于每组连上超级汇点的边，流量为答案，对于每个人
    和他自己有可能所在的组连上流量为1的边即可建图

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 2000;
const int maxm = 2000005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];
bool map[maxn][maxn];

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

bool build(int mid){
    tol = 1;
    memset(po,0,sizeof(po));
    for(int i=1;i<=n;i++){
        add(s,i,1);
        for(int j=0;j<m;j++)
            if(map[i][j])
                add(i,j+n+1,1);
    }
    for(int i=1;i<=m;i++)
        add(i+n,t,mid);
    return sap()==n;
}

void solve(){
    int l = 0,r = n;
    s = n+m+1;
    t = s+1;
    int ans = -1;
    while(l<=r){
        int mid = (l+r)>>1;
        if(build(mid))
            r = mid-1,ans = mid;
        else
            l = mid+1;
    }
    cout<<ans<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m){
        char str[20];
        int val;
        memset(map,0,sizeof(map));
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            while(getchar()!='\n'){
                scanf("%d",&val);
                map[i][val] = 1;
            }
        }
        solve();
    }
    return 0;
}
