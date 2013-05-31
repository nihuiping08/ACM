/*

题目：
    给出一个只有4和7的字符串，有两种操作：
    1.区间反置，把4变成7，把7变成4
    2.询问最长的不下降子序列

分析：
    线段树延迟标记。
    我们需要维护四个域：
    n4  ：表示该区间的右区间连续的4的个数
    n7  ：表示该区间的右区间连续的7的个数
    inc ：表示该区间的右区间连续最长上升子序列的元素个数
    dec ：表示该区间的右区间连续最长上升子序列的元素个数
    所以对于每个节点，需要维护的信息如merge函数所写

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

/******** program ********************/

const int MAXN = 1e6+5;

char s[MAXN];
int n,m;

struct node{
    int l , r;
    int n7 , n4;
    int inc , dec;
    bool rev;
    int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

void merge(int rt){
    tree[rt].rev = false;
    tree[rt].n4 = tree[rt<<1].n4+tree[rt<<1|1].n4;
    tree[rt].n7 = tree[rt<<1].n7+tree[rt<<1|1].n7;
    tree[rt].inc = max(tree[rt<<1].inc+tree[rt<<1|1].n7,tree[rt<<1].n4+tree[rt<<1|1].inc);
    tree[rt].dec = max(tree[rt<<1].dec+tree[rt<<1|1].n4,tree[rt<<1].n7+tree[rt<<1|1].dec);
}

void push_down(int rt){
    tree[rt].rev ^= 1;
    swap(tree[rt].inc,tree[rt].dec);
    swap(tree[rt].n4,tree[rt].n7);
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].rev = false;
    if(l==r){
        tree[rt].n4 = s[l]=='4';
        tree[rt].n7 = s[l]=='7';
        tree[rt].inc = tree[rt].dec = 1;
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    merge(rt);
}

void modify(int l,int r,int rt){
    if(tree[rt].l>=l&&tree[rt].r<=r){
        push_down(rt);
        return;
    }

    if(tree[rt].rev){
        push_down(rt<<1);
        push_down(rt<<1|1);
        tree[rt].rev = false;
    }

    int mid = tree[rt].mid();
    if(r<=mid)
        modify(l,r,rt<<1);
    else if(l>mid)
        modify(l,r,rt<<1|1);
    else{
        modify(l,mid,rt<<1);
        modify(mid+1,r,rt<<1|1);
    }
    merge(rt);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        scanf("%s",s+1);

        build(1,n,1);

        char op[10];
        int x,y;

        while(m--){
            scanf("%s",op);
            if(op[0]=='c')
                printf("%d\n",tree[1].inc);
            else{
                RD2(x,y);
                modify(x,y,1);
            }
        }
    }

	return 0;
}
