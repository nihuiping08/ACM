/*

题目：
    每头牛需要一种食物以及一种饮料，并且一种食物与饮料不能够给两头牛，
    现在问如何安排食物以及饮料，使得奶牛们得到食物以及饮料的数量最大

分析：
    把奶牛拆点，建立超级源点以及超级汇点，超级源点连上食物，超级汇点
    连上饮料，而食物连上相应的奶牛，再建立n个奶牛节点，每头奶牛连上自
    己，再对第二批n头奶牛连上饮料，每条边的流量为1即可

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 405;
const int inf = 1e9;

bool map[maxn][maxn];
int n,food,d,s,t;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];

struct node{
    int y,f,next;
}edge[maxn*maxn];

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

void init(){
    int x,y,z,qq;
    s = n*2+food+d+1;
    t = s+1;
    memset(po,0,sizeof(po));
    tol = 1;
    memset(map,false,sizeof(map));
    for(int i=1;i<=food;i++){
        map[s][i] = true;
        add(s,i,1);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&y);
        qq = food+i;
        while(x--){
            scanf("%d",&z);
            if(map[z][qq])
                continue;
            add(z,qq,1);
            map[z][qq] = 1;
        }
        qq += n;
        while(y--){
            scanf("%d",&z);
            if(map[qq][food+2*n+z])
                continue;
            add(qq,food+2*n+z,1);
            map[qq][food+2*n+z] = 1;
        }
    }
    for(int i=1;i<=d;i++)
        add(i+food+2*n,t,1);

    for(int i=1;i<=n;i++)
        add(food+i,food+i+n,1);
    n = n*2+food+d+2;
}

void sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = n;
    for(int i=1;i<=n;i++)
        arc[i] = po[i];
    int MIN;
    int ans = 0;
    bool ok;
    int aug = inf;
    int i = s;

    while(dis[s]<n){
        cf[i] = aug;
        ok = false;
        for(int j=arc[i];j;j=edge[j].next){
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                if(aug>edge[j].f)
                    aug = edge[j].f;
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    ans += aug;
                    for(;i!=s;i=edge[pre[i]^1].y){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                    }
                    aug = inf;
                }
                break;
            }
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
    printf("%d\n",ans);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>food>>d){
        init();
        sap();
    }
    return 0;
}
