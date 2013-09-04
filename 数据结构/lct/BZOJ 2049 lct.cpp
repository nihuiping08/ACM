/*

题目：
	支持三种操作：
	1.合并子树
	2.分裂子树
	3.询问x是否可达y
	
分析：
	裸的lct，就是link,cut操作。
	交了50多发，TLE了30多发，后来按照别人的代码使用栈下沉标记才过了，囧。
	
	1.access(x)其实就是把路径x到根打通，并且把整条链用splay维护，这棵splay的所有节点就是
	这条路径。
	2.link(x,y)：把两棵子树合并为一棵树。先把x置为根，然后把x的父亲置为y，打通x到根的路径
	即可(貌似可以不用，不理解了，囧啊)。
	3.cut(x,y)：把x和y分离成两棵子树。先把x置为根，然后打通x到根的路径，把y splay到根，把
	y的左儿子与y分离。

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

const int MAXN = 100005;

// 外挂
char op;
inline void Char(){
    while( isupper(op=getchar())==false );
    while( islower(getchar()) );
}
inline void Int(int &x){
    while( isdigit(op=getchar())==false );
    x = op-'0';
    while( isdigit(op=getchar()) )
        x = x*10+op-'0';
}

// LCT部分
struct LCT{

    int ch[MAXN][2],fa[MAXN],tot;
    bool rev[MAXN];
    int sta[MAXN],top;

    inline void push(int x){ // 翻转树的上下关系
        if(!x || !rev[x])return;
        if(ch[x][0])rev[ ch[x][0] ] ^= 1;
        if(ch[x][1])rev[ ch[x][1] ] ^= 1;
        swap(ch[x][0],ch[x][1]);
        rev[x] = 0;
    }

    inline bool isRoot(int x){ // 判断是否为根
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
    }

    inline void splay(int x){
        top = 0;
        sta[++top] = x;
        for(int y=x;!isRoot(y);y=fa[y])
            sta[++top] = fa[y];
        while(top)push(sta[top--]);

        while(!isRoot(x)){
            if(isRoot(fa[x]))rot(x);
            else{
                sgn(x)==sgn(fa[x]) ? rot(fa[x]) : rot(x);
                rot(x);
            }
        }
    }

    inline int access(int x){
        int y = 0;
        for(;x;x=fa[y = x]){
            splay(x);
            ch[x][1] = y;
        }
        return y;
    }

    inline void mRoot(int x){
        rev[ access(x) ] ^= 1;
        splay(x);
    }

    inline int getRoot(int x){
        x = access(x);
        //splay(x);
        while(ch[x][0]){
            x = ch[x][0];
            push(x);
        }
        return x;
    }

    inline bool jud(int x,int y){ // 判断是否同根
        return getRoot(x)==getRoot(y);
    }

    inline bool cut(int x,int y){
        //if(x==y||!jud(x,y))return false;
        mRoot(x);
        access(y);splay(y);
        fa[ ch[y][0] ] = 0;
        ch[y][0] = 0;
        return true;
    }

    inline bool link(int x,int y){
        //if(jud(x,y))return false;
        mRoot(x);
        fa[x] = y;
        access(x);
        return true;
    }

}lct;

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,x,y;
    RD2(n,m);
    while(m--){
        Char();
        if(op=='Q'){
            Int(x);Int(y);
            puts(lct.jud(x,y)?"Yes":"No");
        }else if(op=='C'){
            Int(x);Int(y);
            lct.link(x,y);
        }else if(op=='D'){
            Int(x);Int(y);
            lct.cut(x,y);
        }
    }

    return 0;
}
