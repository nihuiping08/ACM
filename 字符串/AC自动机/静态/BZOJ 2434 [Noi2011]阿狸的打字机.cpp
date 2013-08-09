/*

题目：
输入小写字母，打字机的一个凹槽中会加入这个字母(这个字母加在凹槽的最后)。
按一下印有'B'的按键，打字机凹槽中最后一个字母会消失。
按一下印有'P'的按键，打字机会在纸上打印出凹槽中现有的所有字母并换行，但凹槽中的字母不会消失。
询问：打字机会显示第x个打印的字符串在第y个打印的字符串中出现了多少次

分析：
注意到，x其实就是一个fail树中的父节点，y对应是x的子节点，于是询问变成了询问x的相应的子树
的某个部分的大小。

直接建trie树，需要用栈来保存上一个节点的信息，并且插入时跟以往的不同，具体可以看代码。
建树之后，建立ac自动机，然后fail指针反向建立fail树以及维护进出的时间戳。
再次按照建树时的步骤模拟：
p操作时，目前对应的就是第y个，现在询问x在y中出现的次数，直接
询问树状数组x所在的区间大小。
B操作时，跟上面一样。
其他的话，直接在树状数组相应位置中添加1，表示x的子树增加一。

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

const int MAXN = 2e5+5;
const int kind = 27;

char s[MAXN];

struct BIT{
    int c[MAXN];
    inline void init(){
        Clear(c);
    }
    inline int lowbit(int x){
        return x & -x;
    }
    inline void modify(int x,int val){
        if(x==0)return;
        while(x<MAXN){
            c[x] += val;
            x += lowbit(x);
        }
    }
    inline void update(int x,int y,int val){
        modify(x,val);
        modify(y,-val);
    }
    inline int ask(int x){
        int ans = 0;
        while(x>0){
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
    inline int ask(int x,int y){
        return ask(x)-ask(y);
    }
}bit;

struct AC{
    int ch[MAXN][kind],fail[MAXN],tot;
    int at[MAXN];
    int fin[MAXN],st[MAXN],tol;

    int sta[MAXN],top;
    int ans[MAXN];

    vector<int> adj[MAXN];
    vector< PII > vec[MAXN];

    inline void set(int x){
        Clear(ch[x]);
        fail[x] = 0;
    }

    inline void init(){
        rep(i,MAXN){
            adj[i].clear();
            vec[i].clear();
        }
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

    inline void insert(){
        int len = strlen(s);

        int r = 1;

        int n = 0;
        top = 0;

        rep(i,len){
            if(s[i]=='P')
                at[++n] = r;
            else if(s[i]=='B')
                r = sta[top--];
            else{
                sta[++top] = r;
                int c = ind(s[i]);
                if(ch[r][c]==0)
                    ch[r][c] = newNode();
                r = ch[r][c];
            }
        }
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
        foreach(i,adj[x])
            dfs(adj[x][i]);
        fin[x] = tol;
    }

    inline void run(){
        init();
        bit.init();

        insert();
        build();
        dfs(1);

        int m,x,y;
        RD(m);
        rep1(i,m){
            RD2(x,y);
            vec[y].pb( MP(x,i) );
        }

        int len = strlen(s);
        int r = 1;
        top = 0;
        int n = 0;
        memset(ans,-1,sizeof(ans));

        rep(i,len){
            if(s[i]=='B'){
                bit.modify( st[r],-1 );
                r = sta[top--];
            }
            else if(s[i]=='P'){
                ++ n;
                foreach(j,vec[n]){
                    int x = at[ vec[n][j].first ];
                    int id = vec[n][j].second;
                    ans[id] = bit.ask( fin[x],st[x]-1 );
                }
            }else{
                int c = ind(s[i]);
                sta[++top] = r;
                r = ch[r][c];
                bit.modify( st[ r ],1 );
            }
        }

        rep1(i,m)
            printf("%d\n",ans[i]);
    }
}ac;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(~scanf("%s",s)){
        ncase?puts(""):ncase = 1;
        ac.run();
    }

	return 0;
}

