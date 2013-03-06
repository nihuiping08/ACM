/*

题目：
    给出图的邻接矩阵，现在要重新建设新的路x,y,dis。问从1开始建设，
    到第i条路建设完之后，问每两个城市之间的最短距离之和是多少。

分析：
    我们可以用floyd思想来进行松弛，加入了该路之后，相当于当前的最短路
    加上新建的路能否进行松弛操作

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

const int MAXN = 302;

int a[MAXN][MAXN];
int n;
bool ok;

void floyd(){
    rep1(k,n)
        rep1(i,n)
            rep(j,n)
                a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
}

void relax(){
    int x,y,d;
    RD3(x,y,d);
    ll ans = 0;

    rep1(i,n)
        rep1(j,n){
            int tmp =  min(a[i][x]+a[y][j]+d,a[i][y]+a[x][j]+d);
            a[i][j] = min( a[i][j] ,tmp );
            ans += a[i][j];
        }

    if(ok)
        putchar(' ');
    ok = true;
    cout<<ans/2;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        rep1(i,n)
            rep1(j,n)
                RD(a[i][j]);
        floyd();
        int k;
        RD(k);
        ok = false;
        while(k--)
            relax();
        puts("");
    }
	return 0;
}
