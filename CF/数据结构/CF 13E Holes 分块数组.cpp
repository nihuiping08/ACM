/*

题目：跟这题一模一样http://www.lydsy.com/JudgeOnline/problem.php?id=2002
分析：
    分块数组入门题。
    具体的可以看http://dongxicheng.org/structure/blocklink/

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
#define PQ priority_queue

/******** program ********************/

const int MAXN = 1e5+5;

int fa[MAXN],po[MAXN],sz[MAXN],a[MAXN],n,m;
int end[MAXN];

void make(int x){
    int y = x+a[x];
    if(y>n){
        end[x] = x;
        po[x] = n+1;
        sz[x] = 1;
    }else{
        if(fa[x]==fa[y]){
            end[x] = end[y];
            po[x] = po[y];
            sz[x] = sz[y]+1;
        }else{
            end[x] = x;
            po[x] = y;
            sz[x] = 1;
        }
    }
}

void change(int x,int y){
    a[x] = y;
    for(int i=x;i;i--)
        if(fa[i]==fa[x])
            make(i);
        else
            break;
}

void ask(int x){
    int s = end[x];
    int ans = 0;
    for(int i=x;i<=n;i=po[i]){
        ans += sz[i];
        s = end[i];
    }
    printf("%d %d\n",s,ans);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);

    int block_size = sqrt(n*1.0);
    rep1(i,n){
        RD(a[i]);
        fa[i] = i / block_size;
    }

    for(int i=n;i;i--)
        make(i);

    int x,y,op;
    while(m--){
        RD2(op,x);
        if(op==0){
            RD(y);
            change(x,y);
        }else
            ask(x);
    }

	return 0;
}
