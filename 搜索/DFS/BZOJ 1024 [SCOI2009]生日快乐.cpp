/*

題目：
    windy的生日到了，为了庆祝生日，他的朋友们帮他买了一个边长分别为 X 和 Y
    的矩形蛋糕。 现在包括windy，一共有 N 个人来分这块大蛋糕，要求每个人必须
    获得相同面积的蛋糕。 windy主刀，每一切只能平行于一块蛋糕的一边（任意一
    边），并且必须把这块蛋糕切成两块。 这样，要切成 N 块蛋糕，windy必须切
    N-1 次。 为了使得每块蛋糕看起来漂亮，我们要求 N 块蛋糕的长边与短边的比
    值的最大值最小。 你能帮助windy求出这个比值么？

分析：
    dfs

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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

double dfs(double x,double y,int num){
    if(x>y)
        swap(x,y);
    if(num==1)
        return y/x;
    double per = 1.0/num;
    double ans = 1e20;
    rep1(i,num-1){
        ans = min(ans,max(dfs(x*i*per,y,i),dfs(x-x*i*per,y,num-i)));
        ans = min(ans,max(dfs(x,y*i*per,i),dfs(x,y-y*i*per,num-i)));
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m,s;
    RD3(n,m,s);
    printf("%.6lf\n",dfs(n,m,s));

	return 0;
}
