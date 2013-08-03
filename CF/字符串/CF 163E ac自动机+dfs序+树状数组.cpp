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

const int MAXN = 1.5e6;
const int kind = 26;

char s[MAXN];
bool use[MAXN];

struct BIT{
    int c[2*MAXN];
    inline void init(){
        Clear(c);
    }
    inline int lowbit(int x){
        return x & -x;
    }
    inline void update(int x,int y,int val){
        modify(x,val);
        modify(y,-val);
    }
    inline void modify(int x,int val){
        if(x==0)return;
        while(x<MAXN){
            c[x] += val;
            x += lowbit(x);
        }
    }
    inline int ask(int x){
        int ans = 0;
        while(x>0){
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
}bit;

struct AC{
    int ch[MAXN][kind],fail[MAXN];
    int tot;
    vector<int> adj[MAXN];
    int low[MAXN],dfn[MAXN],tol;
    int at[MAXN];

    inline void set(int x){
        Clear(ch[x]);
        fail[x] = 0;
    }

    inline void init(){
        rep(i,MAXN)
            adj[i].clear();
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

    inline void insert(int id){
        int r = 1;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
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
        low[x] = ++tol;
        foreach(i,adj[x])
            dfs(adj[x][i]);
        dfn[x] = tol;
    }

    inline void run(){
        int len = strlen(s)-1;
        int ans = 0;

        int r = 1;
        rep1(i,len){
            int c = ind(s[i]);
            while(r&&ch[r][c]==0)
                r = fail[r];
            if(r)   r = ch[r][c];
            else    r = 1;
            ans += bit.ask( low[r] );
        }

        printf("%d\n",ans);
    }

}ac;

void cc(int x,int val){
    bit.update( ac.low[ ac.at[x] ],1+ac.dfn[ ac.at[x] ],val );
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>m>>n){
        ac.init();
        bit.init();

        rep1(i,n){
            scanf("%s",s);
            ac.insert(i);
            use[i] = true;
        }

        ac.build();
        ac.dfs(1);

        rep1(x,n)
            cc(x,1);

        int x;
        while(m--){
            scanf("%s",s);
            if(s[0]=='?')
                ac.run();
            else{
                sscanf(s+1,"%d",&x);
                if(use[x]&&s[0]=='-'){
                    use[x] = 0;
                    cc(x,-1);
                }else if(!use[x]&&s[0]=='+'){
                    use[x] = 1;
                    cc(x,1);
                }
            }
        }
    }

	return 0;
}
