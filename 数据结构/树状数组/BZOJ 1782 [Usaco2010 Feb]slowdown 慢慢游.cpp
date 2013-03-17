/*

题目：http://www.lydsy.com/JudgeOnline/problem.php?id=1782
分析：
    若是普通的dfs，是 O(n^2)
    我们发现，其实统计的就是从根节点到该节点的树链上比当前节点小的数的个数。
    所以我们可以用树状数组来维护一下dfs序列即可

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 200005;

int c[MAXN],n;
int po[MAXN],tol;
int id[MAXN];
int ans[MAXN];

struct node{
    int y,next;
}edge[MAXN];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int lowbit(int x){
    return x & -x;
}

void update(int x,int val){
    while(x<=n){
        c[x] += val;
        x += lowbit(x);
    }
}

int ask(int x){
    int ret = 0;
    while(x>0){
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

void dfs(int x,int fa){
    update(id[x],1);
    //cout<<"id[x] =  "<<id[x]<<endl;
    ans[id[x]] = ask(id[x]-1);
    for(int i=po[x];i;i=edge[i].next)
        if(edge[i].y!=fa)
            dfs(edge[i].y,x);
    update(id[x],-1);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    int x,y;
    for(int i=1;i<n;i++){
        RD2(x,y);
        add(x,y);
        add(y,x);
    }

    rep1(i,n){
        RD(x);
        id[x] = i;
    }

    dfs(1,0);

    rep1(i,n)
        printf("%d\n",ans[i]);

	return 0;
}
