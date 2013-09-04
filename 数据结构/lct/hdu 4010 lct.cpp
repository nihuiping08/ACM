/*


支持：
1.添加边 x,y
2.删边 x,y
3.对于路径x,y上的所有节点的值加上w
4.询问路径x,y上的所有节点的最大权值

分析：
裸的lct...
rev忘了清零死循环了两小时。。。

1：就是link操作

2：就是cut操作

3：维护多一个mx域，mx[x]表示在splay中以节点x为根的子树的最大点权，每次修改时，把x置
为splay的根，打通y到x的路径，把y splay到根，那么，直接对y节点的lazy标记加上为w即可。

4：同3操作，把x置为splay的根，打通y到x的路径，把y splay到根，那么，y子树所对应的节点
就是路径x到y的所有节点。

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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 3e5+5;

// 外挂
char op;
inline void Int(int &x){
    while( !isdigit(op=getchar()) );
    x = op-'0';
    while(isdigit(op=getchar()))
        x = x*10+op-'0';
}

struct LCT{
    int ch[MAXN][2],fa[MAXN];
    int lz[MAXN],mx[MAXN],val[MAXN];
    bool rev[MAXN];
    int sta[MAXN],top;

    inline void init(){
        Clear(ch);
        Clear(fa);
        Clear(lz);
        Clear(rev);
        mx[0] = 0;
    }

    inline void modify(int x,int d){ // 单点增加lazy标记
        if(!x)return;
        lz[x] += d;
        mx[x] += d;
        val[x] += d;
    }

    inline void clear(int x){
        if(!x)return;
        if(rev[x]){
            if(ch[x][0])rev[ch[x][0]] ^= 1;
            if(ch[x][1])rev[ch[x][1]] ^= 1;
            swap(ch[x][0],ch[x][1]);
            rev[x] = 0;
        }
        if(lz[x]){
            modify(ch[x][0],lz[x]);
            modify(ch[x][1],lz[x]);
            lz[x] = 0;
        }
    }

    inline void update(int x){
        if(!x)return;
        mx[x] = max( val[x],max(mx[ch[x][0]],mx[ch[x][1]]) );
    }

    inline bool isRoot(int x){
        return !x || !( (ch[ fa[x] ][0]==x) || (ch[ fa[x] ][1]==x) );
    }

    inline bool sgn(int x){
        return ch[ fa[x] ][1]==x;
    }
    inline void setc(int y,int d,int x){
        ch[y][d] = x;
        fa[x] = y;
    }
    inline void rot(int x){
        int y = fa[x] , z = fa[y] , d = sgn(x)^1;
        setc(y,d^1,ch[x][d]);
        if(isRoot(y)) fa[x] = fa[y];
        else setc(z,sgn(y),x);
        setc(x,d,y);
        update(y);
    }

    inline void splay(int x){
        if(!x)return;
        top = 0;
        sta[++top] = x;
        for(int y=x;!isRoot(y);y=fa[y])
            sta[++top] = fa[y];
        while(top)clear(sta[top--]);

        while(!isRoot(x)){
            if(isRoot(fa[x]))rot(x);
            else{
                sgn(x)==sgn(fa[x]) ? rot(fa[x]) : rot(x);
                rot(x);
            }
        }
        update(x);
    }

    inline int access(int x){
        int y = 0;
        for(;x;x=fa[y = x]){
            splay(x);
            ch[x][1] = y;
            update(x);
        }
        return y;
    }

    inline void mRoot(int x){
        rev[ access(x) ] ^= 1;
        splay(x);
    }

    inline int getRoot(int x){
        x = access(x);
        while(ch[x][0]){
            x = ch[x][0];
            clear(x);
        }
        return x;
    }

    inline bool jud(int x,int y){// ok
        return getRoot(x)==getRoot(y);
    }

    inline void link(int x,int y){
        if(jud(x,y)){
            puts("-1");
            return;
        }
        mRoot(x);
        fa[x] = y;
        //access(x);
    }

    inline void cut(int x,int y){
        if(x==y||!jud(x,y)){
            puts("-1");
            return;
        }
        mRoot(x);
        access(y);
        splay(y);
        fa[ ch[y][0] ] = 0;
        ch[y][0] = 0;
        update(y);
    }

    inline void modify(int x,int y,int c){
        if(!jud(x,y)){
            puts("-1");
            return;
        }
        mRoot(x);
        access(y);
        splay(y);
        modify(y,c);
        clear(y);
    }

    inline int ask(int x,int y){
        if(!jud(x,y))
            return -1;
        mRoot(x);
        access(y);
        splay(y);
        return mx[y];
    }

}lct;

struct Edge{
    int y,next;
}edge[MAXN<<1];

int po[MAXN],tol;

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs(int x,int pa){
    lct.fa[x] = pa;
    for(int i=po[x];i;i=edge[i].next)
        if(edge[i].y!=pa)
            dfs(edge[i].y,x);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,w,n,m,op;
    while(~RD(n)){
        lct.init();
        Clear(po);
        tol = 0;

        REP(i,2,n){
            Int(x);Int(y);
            add(x,y);
            add(y,x);
        }

        dfs(1,0);

        rep1(i,n){
            RD(lct.val[i]);
            lct.mx[i] = lct.val[i];
        }
        RD(m);
        while(m--){
            Int(op);
            if(op==1){
                Int(x);Int(y);
                lct.link(x,y);
            }else if(op==2){
                Int(x);Int(y);
                lct.cut(x,y);
            }else if(op==3){
                Int(w);Int(x);Int(y);
                lct.modify(x,y,w);
            }else{
                Int(x);Int(y);
                printf("%d\n",lct.ask(x,y));
            }
        }
        puts("");
    }

    return 0;
}
