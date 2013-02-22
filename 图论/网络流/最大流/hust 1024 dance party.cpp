/*

拆点,二分答案—建图:源点到男孩1的边容量为二分的值,女孩1到汇点
的边容量为二分的值,男孩1到喜欢女孩1的边容量为1,男孩1到男孩2的
边容量为k,男孩2到不喜欢女孩2的边容量为1,女孩2到女孩1的边容量
为k,求最大流

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 2000;
const int maxm = 2000005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t,k;
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
        add(s,i,mid);
        add(i,i+n,k);
        add(i+3*n,i+2*n,k);
        add(i+2*n,t,mid);
        for(int j=1;j<=n;j++){
            if(map[i][j])
                add(i,j+2*n,1);
            else
            add(i+n,j+3*n,1);
        }
    }
    int temp = sap();
    return temp==n*mid;
}

void solve(){
    int l = 0,r = n;
    s = n<<2|1;
    t = s+1;
    int ans = -1;
    while(l<=r){
        int mid = (l+r)>>1;
        if(build(mid))
            l = mid+1,ans = mid;
        else
            r = mid-1;
    }
    cout<<ans<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,x,y;
    cin>>ncase;
    while(ncase--){
        cin>>n>>m>>k;
        memset(map,0,sizeof(map));
        for(int i=0;i<m;i++){
            scanf("%d%d",&x,&y);
            map[x][y] = true;
        }
        solve();
    }
    return 0;
}
