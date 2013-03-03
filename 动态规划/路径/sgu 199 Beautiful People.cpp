/*

题目：
    给出xi,yi，若xi<=xj&&yi>=yj或者xi>=xj&&yi<=yj就会发生冲突，问最大
    能够有多少人在一起的时候不会发生冲突，并给出一种可行的方案

分析：
    我们可以先对x排序，若相等就对y排序。
    再二分求LIS，记录当前位置的前驱所在的位置。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1e5+5;

int dp[MAXN],pre[MAXN];
int n;

struct node{
    int x,y,id;
    friend bool operator < (node a,node b){
        return a.x<b.x || (a.x==b.x&&a.y>b.y);
    }
    void read(int i){
        RD2(x,y);
        id = i;
    }
}p[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    for(int i=1;i<=n;i++)
        p[i].read(i);
    sort(p+1,p+n+1);

    int top = 0;
    dp[++top] = 1;
    pre[1] = 0;
    for(int i=2;i<=n;i++){
        if(p[dp[top]].y<p[i].y){
            dp[++top] = i;
            pre[i] = dp[top-1];
            continue;
        }
        int l = 1,r = top;
        while(l<=r){
            int mid = (l+r)>>1;
            if(p[dp[mid]].y<p[i].y)
                l = mid+1;
            else
                r = mid-1;
        }
        dp[l] = i;
        pre[i] = dp[l-1];
    }

    cout<<top<<endl;

    int id = dp[top];
    printf("%d",p[id].id);
    while(--top){
        id = pre[id];
        printf(" %d",p[id].id);
    }

    puts("");

	return 0;
}
