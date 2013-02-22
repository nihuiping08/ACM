/*

题目：
    给出n个电站以及m个用户，每个用户需要两个电站来供电，现在给出每个电站的修建费用，
    以及每个用户得到供电时的利润，现在问如何安排电站的修建，使得利益最大

分析：
    对于用户来说，可以建立超级源点，建立流量为该用户的利润。
    对于用户需要的电站，建立流量为inf的边。
    对于每个电站，连上超级汇点的边，费用为每个电站的修建费用。
    最后把问题转化为求最小割，然后利用所有用户的利润减掉最大流，即为问题所求

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 55005;
const int maxm = 550005;
const int inf = 1e9;

#define debug puts("here");

int pre[maxn],cf[maxn],dis[maxn],arc[maxn],gap[maxn];
int po[maxn],tol;
int n,m,s,t,tot;

struct node{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].f = 0;
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

void build(){
    int sum = 0;

    int x,y,z;

    s = n+m+1;
    tot = t = n+m+2;

    memset(po,0,sizeof(po));
    tol = 1;

    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        add(i+m,t,x);
        //sum += x;
    }

    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(i,x+m,inf);
        add(i,y+m,inf);
        add(s,i,z);
        sum += z;
    }

    cout<<sum - sap()<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
        build();
    return 0;
}
