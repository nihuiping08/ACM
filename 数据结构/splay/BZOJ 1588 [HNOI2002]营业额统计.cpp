/*

这题是我自己的第一道splay题，只是用来测试一下模板的。。。

题目链接：http://www.lydsy.com/JudgeOnline/problem.php?id=1588

分析：
    这题就是求前驱和后继。旋转跟SBT、AVL、BST、treap一样，并且不需要维护树的平衡，
    默认为90%的询问发生在10%的数据上面，所以我们在插入的时候就把插入的的数据经过
    splay操作旋转该节点至根部。这题在询问x的前驱的时候，我们可以先得到x，然后再把x
    经过splay操作旋转至根部，再找到根的前驱，后继同理。其他的操作以后再总结一下。。

*/
#include <set>
#include <map>
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
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

#define INF 1e9

namespace Splay{

#define X 1111111

#define px pre[x]
#define py pre[y]

#define lx ch[x][0]
#define ly ch[y][0]
#define lz ch[z][0]

#define rx ch[x][1]
#define ry ch[y][1]

    int root,tot;
    int ch[X][2],pre[X],val[X];

    inline void init(){ // 初始化
        root = tot = 0;
        memset(ch,0,sizeof(ch));
        memset(pre,0,sizeof(pre));
        memset(val,0,sizeof(val));
    }

    inline void dfs(int x){ // debug使用
        if(x){
            dfs(lx);
            printf("self = %d , left = %d , right = %d , father = %d\n",x,lx,rx,px);
            dfs(rx);
        }
    }

    inline void new_node(int &x,int father,int v){ // 构造新节点
        x = ++tot;
        pre[x] = father;
        val[x] = v;
        ch[x][0] = ch[x][1] = 0;
    }

    inline void setc(int y,int d,int x){ // 旋转过程的子树的链接
        ch[y][d] = x;
        pre[x] = y;
    }

    inline int sgn(int x){ // 0表示在左，1表示在右
        return ch[px][1]==x;
    }

    inline void _rot(int x,int d){
        int y = px;
        int z = py;

        setc(y,!d,ch[x][d]);//类似SBT，要把其中一个分支先给父节点

        if(z)   //如果父节点不是根结点，则要和父节点的父节点连接起来
            setc(z,sgn(y),x);
        pre[x] = z;

        setc(x,d,y);
    }

    inline void rot(int x){_rot(x,!sgn(x));}
    inline void zag(int x){_rot(x,0);} // 左旋
    inline void zig(int x){_rot(x,1);} // 右旋

    // Splay调整，将根为r的子树调整为goal
    inline int splay(int x,int goal=0){
        while(px!=goal){
            int y = px;
            int z = py;
            if(z==goal){
                rot(x);
                break;
            }
            if(lz==y){
                if(ly==x)
                    zig(y),zig(x);
                else
                    zag(x),zig(x);
            }
            else{
                if(ry==x)
                    zag(y),zag(x);
                else
                    zig(x),zag(x);
            }
        }
        if(goal==0)
            root = x;
        return x;
    }

    inline int insert(int v){ // 插入
        int x = root;
        while(ch[x][ val[x]<v ]){
            if(val[x]==v){
                splay(x); // 已存在，这题可以忽略掉，但是需要旋转该节点作为根
                return 0;
            }
            x = ch[x][ val[x]<v ];
        }
        new_node(ch[x][ val[x]<v ],x,v);
        splay(ch[x][ val[x]<v ]); // 新插入节点splay至根部
        return 1;
    }

    inline int get_pre(int x){ // 得到前驱
        int tmp = x;
        x = lx;
        if(x==0)
            return INF;
        while(rx)
            x = rx;
        return val[tmp]-val[x];
    }

    inline int get_next(int x){ // 得到后继
        int tmp = x;
        x = rx;
        if(x==0)
            return INF;
        while(lx)
            x = lx;
        return val[x]-val[tmp];
    }

#undef X

#undef px
#undef py

#undef lx
#undef ly
#undef lz

#undef rx
#undef ry

}using namespace Splay;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int ans = 0,n,x;
    cin >> n;

    init();
    rep(i,n){
        if(scanf("%d",&x)==EOF)
            x = 0;
        if(i==0){
            ans += x;
            new_node(root,0,x);
            continue;
        }
        if(insert(x)==0)
            continue;
        // 前面插入的时候x已经splay至根部，所以可以直接求值
        ans += min(get_pre(root),get_next(root));
    }
    cout<<ans<<endl;

	return 0;
}
