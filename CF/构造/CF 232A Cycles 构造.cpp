/*

题目：
    构造一个图，使得长度为3的环的数目为m
分析：
    我们可以构造一个不超过长度为3的环数目的完全图，此时假设节点数为n，则长度
    为3的环贡献度为n*(n-1)*(n-2)/6。然后剩下的从新的节点中构造。
    每添加一个新节点，假设添加多k条边，贡献度为k*(k-1)/2。
    然后构造足够即可

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

const int MAXN = 105;

int map[MAXN][MAXN];
int n,m;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    bool ok = false;
    while(~RD(m)){
        ok?puts(""):ok = true;
        memset(map,0,sizeof(map));
        n = 1;
        while(n*(n-1)*(n-2)/6<m)
            n ++;
        n --;
        rep(i,n)
            rep(j,n)
                map[i][j] = (i!=j);

        int ans = n*(n-1)*(n-2)/6;

        while(ans<m){
            int j = 0;
            for(j=n;j;j--)
                if(ans+j*(j-1)/2<=m)
                    break;
            ans += j*(j-1)/2;
            for(int i=0;i<j;i++)
                map[n][i] = map[i][n] = 1;
            n ++;
        }

        cout<<n<<endl;
        rep(i,n){
            rep(j,n)
                cout<<map[i][j];
            puts("");
        }
    }

	return 0;
}
