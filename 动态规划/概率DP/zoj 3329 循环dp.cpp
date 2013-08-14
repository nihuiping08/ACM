/*

题目：
	给出三个多面体，分别有k1,k2,k3个面，三个球抛起落下时为等概率事件，当落到面分别为a,b,c时，
	计数器置零，否则计数器加i+j+k，问计数器到达n时理论上需要多少次

分析：
	设dp[i]表示从i到n的期望。那么，有：
	dp[i] = sigma( dp[i+j]*p[j] )+dp[0]*per+1
	由于每次都有dp[0]出现，之前的做法不太好处理，因此可以增加一个数组表示
	pa[]表示dp[0]出现的概率
	pb[]表示sigma(dp[i+j]*p[j])+1
	因此，期望即为
	pb[0]/(1-pa[i])

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
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1005;

double pa[MAXN],pb[MAXN],p[MAXN];
int n,k1,k2,k3,a,b,c;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD4(n,k1,k2,k3);
        RD3(a,b,c);

        double per = 1.0/(k1*k2*k3);

        Clear(p);
        rep1(i,k1)
        rep1(j,k2)
        rep1(k,k3)
        if(i!=a||j!=b||k!=c)
            p[i+j+k] += per;

        int tot = k1+k2+k3;

        Clear(pa);
        Clear(pb);
        for(int i=n;i>=0;i--){
            pa[i] = per;
            pb[i] = 1;
            rep1(j,tot){
                pa[i] += p[j]*pa[i+j];
                pb[i] += p[j]*pb[i+j];
            }
        }
        printf("%.16lf\n",pb[0]/(1-pa[0]));
    }
	return 0;
}
