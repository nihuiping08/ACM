/*

题目：支持 插入，翻转，删除的功能。
分析：splay的基本操作。
    1.插入，我们需要把插入的位置伸展到根，然后再把伸展之后的后一个位置伸展到根的
    右儿子，插入就直接把所有的数插入到根的右儿子的左子树中。
    2.删除，我们把需要删除的整个区间[a,b]直接伸展到根的右儿子的左子树，即把a-1
    伸展到根，把b+1伸展到根的右儿子，然后把根的右儿子的左子树整个删除掉即可
    3.旋转，lazy标记，每当我们往下遍历的时候，需要把lazy标记下沉。而旋转过程中，比如
    我们需要对区间[a,b]旋转，我们可以把a-1旋转到根，把b+1旋转到根的右儿子，然后把根的
    右儿子的左子树的标记翻转一下就行了。
    4.输出，我们需要输出光标后的第一个字符，我们可以直接把光标的位置伸展到根，然后再
    求根的右儿子的最小值输出
    5.移动到第k个字符后面，我们直接把光标改变，无需把该位置伸展到根，只需要用的时候
    再进行伸展操作
    6.前移（后移），直接把光标减一（加一），无需进行伸展操作

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

int tot,root,pos;

namespace Splay{

#define lx ch[x][0]
#define rx ch[x][1]
#define px pre[x]

#define ly ch[y][0]
#define ry ch[y][1]
#define py pre[y]

#define lz ch[z][0]
#define rz ch[z][1]
#define pz pre[z]

#define rt ch[root][1]
#define lrt ch[rt][0]

    const int X = (1<<21)+5;

    int ch[X][2],pre[X],sz[X],rev[X];
    char str[X];
    char qq[X];

    inline void dfs(int x){
        if(x){
            dfs(lx);
            cout<<lx<<" "<<rx<<" "<<x<<endl;
            dfs(rx);
        }
    }

    inline void update(int x){
        //cout<<lx<<" "<<rx<<" "<<sz[lx]<<" "<<sz[rx]<<" "<<sz[lx]+sz[rx]+1<<endl;
        sz[x] = sz[lx]+sz[rx]+1;
    }

    inline void push_down(int x){
        if(x&&rev[x]){
            swap(lx,rx);
            rev[lx] ^= 1;
            rev[rx] ^= 1;
            rev[x] = 0;
        }
    }

    inline void new_node(int &x,int y,char c){
        x = ++tot;
        pre[x] = y;
        rev[x] = ch[x][0] = ch[x][1] = 0;
        str[x] = c;
    }

    inline void build(int &x,int l,int r,int y,char *s){
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y,s[mid]);
        build(lx,l,mid-1,x,s);
        build(rx,mid+1,r,x,s);
        update(x);
    }

    inline void setc(int y,int d,int x){
        ch[y][d] = x;
        pre[x] = y;
    }

    inline int sgn(int x){
        return ch[px][1]==x;
    }

    inline void _rot(int x,int d){
        int y = px;
        int z = py;
        push_down(y);
        push_down(x);
        setc(y,!d,ch[x][d]);
        if(z)   setc(z,sgn(y),x);
        pre[x] = z;
        setc(x,d,y);
        update(y);
    }

    inline void rot(int x){_rot(x,!sgn(x));}
    inline void zag(int x){_rot(x,0);}
    inline void zig(int x){_rot(x,1);}


    inline int splay(int x,int goal=0){
        push_down(x);
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
        update(x);
        if(goal==0)
            root = x;
        return x;
    }

    inline int get_Kth(int x,int k){
        push_down(x);
        int tmp = sz[lx]+1;
        if(tmp==k)
            return x;
        if(k<tmp)
            return get_Kth(lx,k);
        else
            return get_Kth(rx,k-tmp);
    }

    inline int get_min(int x){
        push_down(x);
        while(lx){
            x = lx;
            push_down(x);
        }
        return x;
    }

    inline void Move(){
        int k;
        scanf("%d",&k);
        pos = k+1;
    }

    inline void Insert(){
        int k;
        scanf("%d",&k);
        getchar();
        gets(qq);
        int x = get_Kth(root,pos);
        splay(x);
        x = get_min(rt);
        splay(x,root);
        build(lrt,0,k-1,rt,qq);
    }

    inline void Delete(){
        int k;
        scanf("%d",&k);
        int x = get_Kth(root,pos);
        splay(x);
        int y = get_Kth(root,pos+k+1);
        splay(y,root);

        pre[lrt] = 0;
        lrt = 0;
        update(rt);
        update(root);
    }

    inline void Rotate(){
        int k;
        scanf("%d",&k);
        int x = get_Kth(root,pos);
        splay(x);
        int y = get_Kth(root,pos+k+1);
        splay(y,root);
        rev[lrt] ^= 1;
    }

    inline void Get(){
        int x = get_Kth(root,pos);
        splay(x);
        x = get_min(rt);
        printf("%c\n",str[x]);
    }

    inline void Prev(){
        pos --;
    }

    inline void Next(){
        pos ++;
    }

    inline void init(){
        memset(pre,0,sizeof(pre));
        memset(ch,0,sizeof(ch));
        memset(sz,0,sizeof(sz));
        memset(rev,0,sizeof(rev));
        root = tot = 0;
        char s[] = "@@@@@@";
        build(root,0,5,0,s);
        pos = 1;
    }

}using namespace Splay;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    char op[20];
    cin>>ncase;
    init();
    while(ncase--){
        scanf("%s",op);
        switch(op[0]){
            case 'M':Move();break;
            case 'I':Insert();break;
            case 'D':Delete();break;
            case 'R':Rotate();break;
            case 'G':Get();break;
            case 'P':Prev();break;
            default:Next();
        }
    }
	return 0;
}
