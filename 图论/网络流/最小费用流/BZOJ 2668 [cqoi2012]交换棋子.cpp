/*

题目：
    有一个n行m列的黑白棋盘，你每次可以交换两个相邻格子（相邻是指有公共边或公共
    顶点）中的棋子，最终达到目标状态。要求第i行第j列的格子只能参与m[i,j]次交换。

分析：
    由于每个棋子（0或者1）都可以看成相同的。011中，第三个和第二个棋子可以看成
    是等价的，所以我们可以建立网络流（最小费用流），使得第三个棋子可以走到第一
    个棋子的位置上。

*/
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 805;
const int MAXM = 1e5;
const int INF = 1e9;

int pre[MAXN],dis[MAXN],arc[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int n,m,s,t,ans,flow;
string a[22],b[22],str;

int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};

struct node{
    int y,f,cost,next;
}edge[MAXM];

void add(int x,int y,int f,int c){
    edge[++tol].y = y;
    edge[tol].cost = c;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}

bool spfa(){
    memset(use,false,sizeof(use));
    rep(i,1000)
        dis[i] = INF;
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    pre[s] = 0;
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&edge[i].cost+dis[x]<dis[y]){
                dis[y] = dis[x]+edge[i].cost;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    if(dis[t]==INF)
        return false;

    int aug = INF;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }

    flow += dis[t];
    ans --;

    return true;
}

int id(int x,int y){
    return x*m+y+1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep(i,n){
        cin>>a[i];
        foreach(j,a[i])
            ans += a[i][j]=='1';
    }
    int cnt = 0;
    rep(i,n){
        cin>>b[i];
        foreach(j,b[i])
            cnt += b[i][j]=='1';
    }
    if(cnt!=ans){
        puts("-1");
        return false;
    }

    s = n*m<<1|1;
    t = s+1;
    tol = 1;

    rep(i,n){
        cin>>str;
        foreach(j,str){
            int c = str[j]-'0';
            int x = 2*id(i,j);
            if(a[i][j]==b[i][j]){
                add(x-1,x,c>>1,0); // 相等的时候，只能够交换偶数次
                add(x,x-1,0,0);
                ans -= a[i][j]=='1';
            }else{
                if(c==0){
                    puts("-1");
                    return 0;
                }
                add(x-1,x,(c+1)/2,0); // 不相等的时候，只能交换奇数次
                add(x,x-1,0,0);
                if(a[i][j]=='1'){
                    add(s,x-1,1,0);
                    add(x-1,s,0,0);
                }else{
                    add(x,t,1,0);
                    add(t,x,0,0);
                }
            }
        }
    }

    rep(i,n)
        rep(j,m)
            rep(k,8){
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||y<0||x>=n||y>=m)
                    continue;
                y = id(x,y);
                x = id(i,j);
                add(2*x,2*y-1,INF,1);
                add(2*y-1,x<<1,0,-1);
            }

    while(spfa())
        ;
    if(ans)
        puts("-1");
    else
        printf("%d\n",flow);

	return 0;
}
