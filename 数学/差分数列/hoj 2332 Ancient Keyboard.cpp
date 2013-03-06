/*

题目：大概意思是说在[a,b)加上1，最后把数字转换为A-Z。问最后的序列
分析：差分数列。。。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1005;

int a[MAXN],n;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        char op[2];
        memset(a,0,sizeof(a));
        while(n--){
            cin>>op;
            RD2(x,y);
            a[x] ++;
            a[y] --;
        }
        REP(i,1,MAXN)
            a[i] += a[i-1];
        rep(i,MAXN)
            if(a[i])
                cout<<(char)(a[i]-1+'A');
        puts("");
    }

	return 0;
}
