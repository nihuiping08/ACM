/*

題目：
    相信大家都玩过扫雷的游戏。那是在一个n*m的矩阵里面有一些雷，要你根
    据一些信息找出雷来。万圣节到了，“余”人国流行起了一种简单的扫雷游
    戏，这个游戏规则和扫雷一样，如果某个格子没有雷，那么它里面的数字
    表示和它8连通的格子里面雷的数目。现在棋盘是n×2的，第一列里面某些格
    子是雷，而第二列没有雷，如下图： 由于第一列的雷可能有多种方案满足
    第二列的数的限制，你的任务即根据第二列的信息确定第一列雷有多少种
    摆放方案。
分析：
    其實有很多都是可以算出來的。。。
    這裡用的方法為：
    算出第三個，然後枚舉1,2，判斷是否符合

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

const int MAXN = 1e4+5;

int a[MAXN],n;
int x[MAXN];

bool ok(){
    if(x[1]+x[2]!=a[1])
        return false;
    for(int i=3;i<n;i++){
        x[i+1] = a[i]-x[i]-x[i-1];
        if(x[i+1]<0||x[i+1]>1)
            return false;
    }
    if(x[n]+x[n-1]!=a[n])
        return false;
    return true;
}

void solve(){
    int ans = 0;
    rep(i,2)
        rep(j,2){
            x[1] = i;
            x[2] = j;
            x[3] = a[2]-a[1];
            ans += ok();
        }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        rep1(i,n)
            RD(a[i]);
        if(n==1){
            if(a[1]<2)
                puts("1");
            else
                puts("0");
        }else if(n==2){
            if(a[1]!=a[2])
                puts("0");
            else
                printf("%d\n",a[1]+1);
        }else
            solve();
    }

	return 0;
}
