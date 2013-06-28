/*

题目：
    给出三种操作：
    1.增加点(x,y)
    2.删除点(x,y)
    3.询问在点(x,y)右上方的点，如果有相同，输出最左边的，如果还有相同，输出最低的那个点
	
分析：
	线段树套平衡树。
	我们先离散化输入的x坐标，然后以每个坐标建立一棵平衡树来维护，这里可以直接用set或者map来维护就行了。
	
	然后我们现在需要在x的右方找到最左最下大于(x,y)的点。
	建立一棵线段树，维护的是区间的纵坐标的最值，而线段树的端点为离散后x的值。
	
	1.我们每次插入的时候，直接在相应的平衡树中插入，然后更新一下线段树的区间最值。
	2.删除时，直接删掉，更新一下最值。
	3.询问时，对于整个区间，我们找到比x大的区间，利用区间最值，从左往右找是否存在大于y的点。最后输出即可。
	关键看代码。。。
	

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

/******** program ********************/

const int MAXN = 2e5+5;

int id[MAXN];
set<int> se[MAXN];

struct Data{
    char op;
    int x,y;
}d[MAXN];

struct node{
    int l,r,mx;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){ // 建树
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].mx = -1;
    if(l==r){
        se[l].clear();	// 平衡树清空
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void update(int x,int rt){ // 更新操作
    if(tree[rt].l==tree[rt].r){
        if(se[x].size()==0) // 如果为空
            tree[rt].mx = -1;
        else{
            set<int>::iterator it = se[x].end(); // 最大值其实就是最后一个元素
            tree[rt].mx = *--it;
        }
        return;
    }
    int mid = tree[rt].mid();
    if(x<=mid)   update(x,rt<<1);
    else        update(x,rt<<1|1);
    tree[rt].mx = max(tree[rt<<1].mx,tree[rt<<1|1].mx);
}

int ask(int x,int y,int rt){
    if(tree[rt].l==tree[rt].r)
        return tree[rt].l;
    if( tree[rt<<1].r>x && tree[rt<<1].mx>y ){ // 如果左儿子区间存在比x大且最值大于y，可能在左儿子区间
        int t = ask(x,y,rt<<1);
        if(t!=-1)   return t;
    }
    if( tree[rt<<1|1].mx>y ) // 这里右儿子的右端点显然比x大
        return ask(x,y,rt<<1|1);
    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    int ncase = 0;
    while(cin>>n){
        ncase?puts("----------------"):ncase = 1;
        char op[10];
        vector<int> vec;
        rep1(i,n){
            scanf("%s%d%d",op,&d[i].x,&d[i].y);
            d[i].op = op[0];
            vec.pb(d[i].x);
        }
        sort(All(vec));
        vec.erase( unique(All(vec)),vec.end() ); // 去重
        foreach(i,vec)
            id[i] = vec[i];
        int len = vec.size();

        build(0,len+10,1);

        rep1(i,n){
            int x = lower_bound(id,id+len,d[i].x)-id+1; // 二分出x离散后的值
			
            int y = d[i].y;
            if(d[i].op=='a'){
                se[x].insert(y);
                update(x,1);
            }
            else if(d[i].op=='r'){
                se[x].erase(y);
                update(x,1);
            }
            else{
                int t = ask(x,y,1);
                if(t==-1)
                    puts("-1");
                else
                    printf("%d %d\n",id[t-1],*se[t].upper_bound(y)); // 二分出比y大的值
            }
        }
    }


	return 0;
}
