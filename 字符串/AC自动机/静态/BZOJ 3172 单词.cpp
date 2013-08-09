/*

某人读论文，一篇论文是由许多单词组成。但他发现一个单词会在论文中出现很多次，现在想知道每个
单词分别在论文中出现多少次。

分析：
建立ac知道自动机之后，构造fail树，发现其实每个节点出现的次数就是以该节点为根的子树插入时
走过的次数的和

*/
#include <set>
#include <map>
#include <list>
#include <cmath>
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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 2e6+5;
const int kind = 26;

char s[MAXN];

struct AC{
    int ch[MAXN][kind],fail[MAXN],tot;
    int at[MAXN],ed[MAXN];
    int fin[MAXN],st[MAXN],tol;

    int sta[MAXN],top;
    int ans[MAXN];

    vector<int> adj[MAXN];

    inline void set(int x){
        Clear(ch[x]);
        fail[x] = ed[x] = 0;
    }

    inline void init(){
        rep(i,MAXN)
            adj[i].clear();
        Clear(ans);
        set(1);
        tot = 1;
        tol = 0;
    }

    inline int newNode(){
        set(++tot);
        return tot;
    }

    inline int ind(char c){
        return c-'a';
    }

    inline void insert(int len,int id){
        int r = 1;
        rep(i,len){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
            ans[r] ++;
        }
        ed[r] = id;
        at[id] = r;
    }

    inline void build(){
        queue<int> q;
        q.push(1);
        while(!q.empty()){
            int r = q.front();
            q.pop();
            if(fail[r])
                adj[ fail[r] ].pb(r);
            rep(c,kind){
                int x = ch[r][c];
                if(!x)continue;
                q.push(x);

                int y = fail[r];
                while(y&&ch[y][c]==0)
                    y = fail[y];
                fail[x] = y?ch[y][c]:1;
            }
        }
    }

    void dfs(int x){
        st[x] = ++tol;
        foreach(i,adj[x]){
            dfs(adj[x][i]);
            ans[x] += ans[ adj[x][i] ];
        }
        fin[x] = tol;
    }

    void run(int n){
        rep1(i,n)
            printf("%d\n",ans[ at[i] ]);
    }

}ac;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0,n;
    while(cin>>n){
        ncase?puts(""):ncase = 1;
        ac.init();

        rep1(i,n){
            scanf("%s",s);
            int l = strlen(s);
            ac.insert(l,i);
        }
        ac.build();
        ac.dfs(1);
        ac.run(n);
    }

	return 0;
}

