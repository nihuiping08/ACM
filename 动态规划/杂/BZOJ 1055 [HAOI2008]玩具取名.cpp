/*

題目：
    某人有一套玩具，并想法给玩具命名。首先他选择WING四个字母中的任意一
    个字母作为玩具的基本名字。然后他会根据自己的喜好，将名字中任意一个
    字母用“WING”中任意两个字母代替，使得自己的名字能够扩充得很长。 现
    在，他想请你猜猜某一个很长的名字，最初可能是由哪几个字母变形过来的。

分析：
    dp[i][j][k]表示從i到j是否可以由第k個字符轉化來
    用記憶化搜索做的話，邊界條件比較好控制些~~

    搜索函數dfs(L,r)
    我們可以枚舉中間分界點i，通過判斷區間[L,i]轉化為字符j，區間[i+1,r]
    轉化的字符k，判斷字符jk是否可以轉化為一個字符

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 202;

int dp[MAXN][MAXN][4];
int num[4],n;
char s[402];
int a[405];
map<char,int> id;
vector<int> vec[4][4];

void dfs(int l,int r){
    if(dp[l][r][0]!=-1)
        return;

    int x = a[l] , y = a[r];

    if(l+1==r){
        foreach(i,vec[x][y])
            dp[l][r][ vec[x][y][i] ] = true;
        rep(i,4)
            if(dp[l][r][i]==-1)
                dp[l][r][i] = 0;
        return;
    }

     // 判斷區間[l,i]轉化為字符j，是否可以與區間[i+1,r]轉化的字符由一個字符轉化而來
    for(int i=l;i<r;i++){
        dfs(l,i);
        rep(j,4)
            if(dp[l][i][j]==1){
                dfs(i+1,r);
                rep(k,4)
                    if(dp[i+1][r][k]==1)
                        foreach(q,vec[j][k])
                            dp[l][r][vec[j][k][q]] = true;
            }
    }

    rep(i,4)
        if(dp[l][r][i]==-1)
            dp[l][r][i] = 0;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    id['W'] = 0;
    id['I'] = 1;
    id['N'] = 2;
    id['G'] = 3;
    rep(i,4)
        RD(num[i]);

    rep(i,4)
        rep(j,num[i]){
            scanf("%s",s);
            vec[ id[ s[0] ] ][ id[ s[1] ] ].pb(i);
        }

    scanf("%s",s+1);
    n = strlen(s+1);

    memset(dp,-1,sizeof(dp));
    rep1(i,n){
        a[i] = id[s[i]];
        dp[i][i][a[i]] = 1;
    }

    dfs(1,n);

    bool ok = false;

    s[0] = 'W';
    s[1] = 'I';
    s[2] = 'N';
    s[3] = 'G';
    for(int i=0;i<4;i++)
        if(dp[1][n][i]){
            ok = true;
            printf("%c",s[i]);
        }
    if(!ok)
        puts("The name is wrong!");
    else
        puts("");
	return 0;
}
