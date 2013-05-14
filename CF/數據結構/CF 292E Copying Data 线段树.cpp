/*

题目：
    有两个数列a,b。有两种操作：
    1.把a数列的第x项到x+k项复制到b数列的y到y+k项
    2.询问y[i]值

分析：
    线段树lazy操作。
    1.对于每个区间节点，维护是第几个插入。
    2.询问的时候直接下沉到该位置，然后用该节点的值进行判断是a数列中
    的哪个值或者就是b数列的值。

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

#define lx (rt<<1)
#define rx (rt<<1|1)
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

const int MAXN = 4e5+5;

int a[MAXN],b[MAXN],n,m;
int x[MAXN],y[MAXN];
int now[MAXN];
bool col[MAXN];

void push(int rt){
    if(!col[rt])    return;
    now[lx] = now[rx] = now[rt];
    col[lx] = col[rx] = col[rt];
    col[rt] = false;
}

void modify(int l,int r,int L,int R,int x,int rt){
    if(l>=L&&r<=R){
        now[rt] = x;
        col[rt] = true;
        return;
    }
    //cout<<l<<" "<<r<<endl;
    push(rt);
    int mid = (l+r)/2;
    if(L<=mid)  modify(l,mid,L,R,x,lx);
    if(R>mid)   modify(mid+1,r,L,R,x,rx);
}

int ask(int l,int r,int pos,int rt){
    if(l==r)
        return now[rt];
    push(rt);
    int mid = (l+r)/2;
    if(pos<=mid)  return ask(l,mid,pos,lx);
    else        return ask(mid+1,r,pos,rx);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep1(i,n)
        RD(a[i]);
    rep1(i,n)
        RD(b[i]);

    int len,op;
    rep1(i,m){
        RD(op);
        //cout<<"i = "<<i<<endl;
        if(op==1){
            RD3(x[i],y[i],len);
            modify(1,n,y[i],y[i]+len-1,i,1);
        }else{
            RD(len);
            int ans = ask(1,n,len,1);
            if(ans) printf("%d\n", a[ len-y[ans]+x[ans] ] );
            else    printf("%d\n",b[len]);
        }
    }

	return 0;
}
