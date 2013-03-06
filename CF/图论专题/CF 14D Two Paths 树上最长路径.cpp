/*

题目：从树中选择两条不想交的路线，使得路线长度的乘积最大
分析：我们可以枚举删掉其中一条边，然后分别求该树的最长路径长度即可

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 205;

int a[MAXN][MAXN],n;
int ans;

int dfs(int x,int fa){
    int max_1 = 0,max_2 = 0;
    rep1(i,n){
        if(a[x][i] && fa!=i){
            int tmp = dfs(i,x);
            if(tmp>max_1){
                max_2 = max_1;
                max_1 = tmp;
            }else if(tmp>max_2)
                max_2 = tmp;
        }
    }

    ans = max(max_1 + max_2,ans);
    return max_1+1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        memset(a,0,sizeof(a));
        int x,y;
        rep(i,n-1){
            RD2(x,y);
            a[x][y] = a[y][x] = 1;
        }

        int qq = 0;
        rep1(i,n)
            for(int j=i+1;j<=n;j++)
                if(a[i][j]){

                    ans = 0;
                    dfs(i,j);

                    int tmp = ans;

                    ans = 0;
                    dfs(j,i);

                    tmp *= ans;
                    qq = max(tmp,qq);
                }

        cout<<qq<<endl;
    }

	return 0;
}
