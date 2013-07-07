/*

题目：
    给出n个红点以及m个蓝点，任意三个点不共线，问由三个红点组成的三角形中
    有多少个内部不包含蓝点。

分析：
    用dp[i][j]统计在线段[i,j]正上方拥有多少个蓝点，然后枚举三角形a,b,c
    a<b<c(横坐标)，所以有 dp[a][b]+dp[b][c] = dp[a][c]，另外得要加上左端点
    或者右端点

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

/******** program ********************/

const int MAXN = 505;

int dp[MAXN][MAXN];

struct node{
    ll x,y;
    void rd(){
        cin>>x>>y;
    }
}a[MAXN],b[MAXN];

ll det(node a,node b,node o){
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>n>>m){
        rep1(i,n)
            a[i].rd();
        rep1(i,m)
            b[i].rd();

        memset(dp,0,sizeof(dp));
        rep1(i,n)
            rep1(j,n){
                if(a[i].x>=a[j].x)
                    continue;
                rep1(k,m){
                    if(b[k].x<a[i].x||b[k].x>=a[j].x)
                        continue;
                    ll t = det( b[k],a[j],a[i] );
                    if(t<0) dp[i][j] ++;
                }
                dp[j][i] = -dp[i][j];
            }

        int ans = 0;
        rep1(i,n)
            REP(j,i+1,n)
                REP(k,j+1,n)
                    if(dp[i][j]+dp[j][k]==dp[i][k])
                        ans ++;
        cout<<ans<<endl;
    }
	return 0;
}

