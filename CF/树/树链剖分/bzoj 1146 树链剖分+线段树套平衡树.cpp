/*

　感觉树链剖分其实是一种思想，不是一种特定的数据结构。它主要是把树中的边划分为轻边和重边，相邻的重边形成一条链，该链载线段树上是一段连续的区间，使得每次访问树链(a,b)的复杂度降下。
　　这题求的是树链上第k大元素（不是第k小），我们可以先进行树链剖分，建立一棵线段树。线段树上的每个节点是一棵平衡树，平衡树上面维护着该节点所在区间的所有元素。
　　
　　对于第一次插入时，我们直接对于每个线段树上的节点建立一棵平衡树（我的代码使用splay），该平衡树能够解决查询第k大元素、查询某值val的排名、插入、删除等问题。
　　对于修改操作，我们直接在线段树中相应的位置修改，但我们访问到区间[l,r]，在该节点的平衡树上需要删除掉原来的值，删除后再把新值插入到该平衡树。
　　对于询问操作，我们通过二分答案，跟普通的树链剖分一样在线段树上进行区间统计，当访问到最终节点（实际上是线段树的一个区间），通过平衡树查询比二分的值大的元素的个数。最后通过判断与k的关系确定下一步。
 
　　我的代码感觉很常规，使用了数组（写指针太麻烦了）来记录splay的节点，就是速度有点慢，我差点以为他TLE了。。。

*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 400005;
const int MAXM = 2500005;
const int INF = 1e8+5;

int sz[MAXN],son[MAXN],dep[MAXN],top[MAXN],fa[MAXN],tid[MAXN],tim;
bool use[MAXN];
int val[MAXN];
int po[MAXN],tol;
int now;

struct segTree{
    int root;
    int l,r,val;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN];

struct Edge{
    int y,next;
}edge[MAXN];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

// splay部分
struct node{
    int ch[MAXM][2],sz[MAXM],val[MAXM],fa[MAXM];
    int tot;

    // 初始化根 ok
    inline void init(int &x){
        newNode(x,0,-1);
        newNode(ch[x][1],x,INF+10);
        update(ch[x][1]);
        update(x);
    }

    // 新的节点 ok
    inline void newNode(int &x,int y,int c){
        x = ++ tot;
        sz[x] = 1;
        ch[x][0] = ch[x][1] = 0;
        val[x] = c;
        fa[x] = y;
    }

    // 更新 ok
    inline void update(int x){
        if(!x)return;
        sz[x] = sz[ ch[x][0] ]+sz[ ch[x][1] ]+1;
    }

    // 旋转 ok
    inline int sgn(int x){
        return ch[ fa[x] ][1] == x;
    }
    inline void setc(int y,int d,int x){
        ch[y][d] = x;
        fa[x] = y;
    }
    inline void rot(int x,int d){
        int y = fa[x];
        int z = fa[y];
        setc(y,!d,ch[x][d]);
        if(z)setc(z,sgn(y),x);
        fa[x] = z;
        setc(x,d,y);
        update(y);
    }

    // splay操作 ok
    inline void splay(int x,int goal=0){
        if(!x)return;
        while(fa[x]!=goal){
            int y = fa[x];
            int z = fa[y];
            if(z==goal){
                rot(x,!sgn(x));
                break;
            }else if(ch[z][0]==y){
                ch[y][0]==x ? rot(y,1) : rot(x,0);
                rot(x,1);
            }else{
                ch[y][1]==x? rot(y,0) : rot(x,1);
                rot(x,0);
            }
        }
        update(x);
        if(!goal)tree[now].root = x;
    }

    // 得到第k大元素 ok
    inline int getKth(int x,int k){
        while(x){
            if(sz[ ch[x][0] ]+1==k)
                return x;
            else if( sz[ ch[x][0] ]+1>k )
                x = ch[x][0];
            else{
                k -= sz[ ch[x][0] ]+1;
                x = ch[x][1];
            }
        }
        return x;
    }

    // 得到值c得排名 ok
    inline int getSz(int c){
        int x = tree[now].root;
        int ans = 0;
        while(x){
            if(val[x]<=c){
                ans += sz[ ch[x][0] ]+1;
                x = ch[x][1];
            }else
                x = ch[x][0];
        }
        return ans;
    }

    // 得到比c值大的数的个数 ok
    inline int getMax(int c){
        int x = tree[now].root;
        int ans = 0;
        while(x){
            if(val[x]>=c){
                ans += sz[ ch[x][1] ]+1;
                x = ch[x][0];
            }else
                x = ch[x][1];
        }
        return ans;
    }

    // 插入
    inline void ins(int c){
        int k = getSz(c);

        splay( getKth(tree[now].root,k),0 );
        splay( getKth(tree[now].root,k+1),tree[now].root );

        int root = tree[now].root;
        newNode( ch[ ch[root][1] ][0] ,ch[root][1] , c  );
        update(ch[root][1]);
        update(root);
    }

    // 删除，保证有元素c
    inline void del(int c){
        int k = getSz(c);

        splay( getKth(tree[now].root,k-1),0 );
        splay( getKth(tree[now].root,k+1),tree[now].root );

        val[ch[ ch[tree[now].root][1] ][0]] = fa[ ch[ ch[tree[now].root][1] ][0] ] = 0;
        ch[ ch[tree[now].root][1] ][0] = 0;

        update( ch[tree[now].root][1] );
        update(tree[now].root);
    }
}sp;

// 树链剖分部分 ok
void dfsFind(int x,int pa,int depth){
    dep[x] = depth;
    fa[x] = pa;
    sz[x] = 1;
    son[x] = 0;
    use[x] = true;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        dfsFind(y,x,depth+1);
        sz[x] += sz[y];
        if(sz[y]>sz[ son[x] ])
            son[x] = y;
    }
}

void dfsCon(int x,int pa){
    use[x] = true;
    top[x] = pa;
    tid[x] = ++ tim;
    if(son[x])dfsCon(son[x],pa);
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        dfsCon(y,y);
    }
}

// 线段树部分
// 建树
void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r)
        return;
    int mid = (l+r)>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

// 修改，把原来的del删除，插入新值c
void modify(int pos,int c,int del,int rt){
    now = rt;
    if(del!=-1)sp.del( del );

    if(!tree[rt].root)
        sp.init(tree[rt].root);
    sp.ins( c );

    if(tree[rt].l==tree[rt].r)
        return;
    int mid = tree[rt].mid();
    if(pos<=mid)
        modify(pos,c,del,rt<<1);
    else
        modify(pos,c,del,rt<<1|1);
}

// 在区间[l,r]中查询比c大的数的个数
int ask(int l,int r,int c,int rt){
    now = rt;
    if(tree[rt].l==l&&tree[rt].r==r)
        return sp.getMax( c )-1;
    int mid = tree[rt].mid();
    if(r<=mid)
        return ask(l,r,c,rt<<1);
    else if(l>mid)
        return ask(l,r,c,rt<<1|1);
    else
        return ask(l,mid,c,rt<<1)+ask(mid+1,r,c,rt<<1|1);
}

inline int cc(int k,int a,int b,int mid){
    int ans = 0;
    while(top[a]!=top[b]){ // 新型lca求法
        if( dep[ top[a] ] < dep[ top[b] ] )
            swap(a,b);
        ans += ask( tid[ top[a] ] , tid[a] , mid , 1 );
        a = fa[ top[a] ];
    }
    if(dep[a]>dep[b])
        swap(a,b);
    ans += ask(tid[a],tid[b],mid,1);
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,x,y,k;
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);

        memset(po,0,sizeof(po));
        tol = 1;
        for(int i=1;i<n;i++){
            scanf("%d%d",&x,&y);
            add(x,y);
            add(y,x);
        }

        // 树链剖分
        memset(use,false,sizeof(use));
        dfsFind(1,1,1);

        memset(use,false,sizeof(use));
        tim = 0;
        dfsCon(1,1);

        // 建立线段树
        build(1,n,1);
        for(int i=1;i<=n;i++)
            modify(tid[i],val[i],-1,1);

        while(m--){
            scanf("%d%d%d",&k,&x,&y);
            if(!k){
                modify( tid[x],y,val[x],1 );
                val[x] = y;
            }else{
                int ans = -1;
                int l = 0 , r = INF;
                while(l<=r){
                    int mid = (l+r)>>1;
                    int tmp = cc(k,x,y,mid);
                    if(tmp>=k){
                        ans = mid;
                        l = mid+1;
                    }else
                        r = mid-1;
                }
                if(ans==-1)
                    puts("invalid request!");
                else
                    printf("%d\n",ans);
            }
        }
    }
    return 0;
}
