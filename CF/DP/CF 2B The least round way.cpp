/*

题目：
	方格中有数，求从左上到右下所经过的格子的数相乘时最少后缀0的路径
分析：
	DP。只用考虑2和5的个数。另外需要注意存在0的情况。

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 1005;
const __int64 inf = 2e16;
#define debug puts("hrer");

__int64 a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],n;
__int64 dp[maxn][maxn],pre[maxn][maxn][2],path[maxn][maxn][2];
__int64 ret,top;
char s[maxn*2];

void dfs2(int x,int y)
{
    ret += c[x][y];
    int xx = pre[x][y][0];
    int yy = pre[x][y][1];
    if(xx&&yy)
        dfs2(xx,yy);
    else
        return;
    if(pre[x][y][0]+1==x)
        s[top++] = 'D';
    else
        s[top++] = 'R';
}

void dfs5(int x,int y)
{
    ret += c[x][y];
    if(path[x][y][0]&&path[x][y][1])
        dfs5(path[x][y][0],path[x][y][1]);
    else
        return;
    if(path[x][y][0]+1==x)
        s[top++] = 'D';
    else
        s[top++] = 'R';
}

int main()
{
    //freopen("sum.in","r",stdin);
    __int64 x;
    while(cin>>n){
        memset(pre,0,sizeof(pre));
        memset(path,0,sizeof(path));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        bool ok = false;
        int posx,posy;

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                scanf("%I64d",&a[i][j]);
                if(a[i][j]==0){
                    a[i][j] = 10;
                    if(!ok){
                        ok = true;
                        posx = i;
                        posy = j;
                    }
                }
                x = a[i][j];
                while(x&&(x&1)==0){
                    b[i][j]++;
                    x = x>>1;
                }
                x = a[i][j];
                while(x&&x%5==0){
                    c[i][j]++;
                    x /= 5;
                }
            }

        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                dp[i][j] = inf;
        dp[0][1] = dp[1][0] = dp[0][0] = 0;

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(dp[i-1][j]<=dp[i][j-1]){
                    pre[i][j][0] = i-1;
                    pre[i][j][1] = j;
                }
                else{
                    pre[i][j][0] = i;
                    pre[i][j][1] = j-1;
                }
                dp[i][j] = min(dp[i-1][j],dp[i][j-1])+b[i][j];
            }

        __int64 ans = dp[n][n];

        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                dp[i][j] = inf;
        dp[0][1] = dp[1][0] = 0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(dp[i-1][j]<=dp[i][j-1]){
                    path[i][j][0] = i-1;
                    path[i][j][1] = j;
                }
                else{
                    path[i][j][0] = i;
                    path[i][j][1] = j-1;
                }
                dp[i][j] = min(dp[i-1][j],dp[i][j-1])+c[i][j];
            }
        ret = 0;
        //cout<<dp[n][n]<<"  "<<ans<<endl;
        top = 0;
        if(dp[n][n]>1&&ans>1&&ok)
        {
            cout<<1<<endl;
            for(int i=1;i<posx;i++)
                putchar('D');
            for(int j=1;j<posy;j++)
                putchar('R');
            for(int i=posx;i<n;i++)
                putchar('D');
            for(int j=posy;j<n;j++)
                putchar('R');
            puts("");
            continue;
        }
        if(dp[n][n]>=ans)
        {
            dfs2(n,n);
            //cout<<ans<<" "<<ret<<endl;
            printf("%I64d\n",min(ans,ret));
            s[top] = '\0';
            puts(s);
        }
        else
        {
            //debug;
            dfs5(n,n);
            //cout<<ans<<" "<<ret<<endl;
            printf("%I64d\n",min(dp[n][n],ret));
            s[top] = '\0';
            puts(s);
        }
    }
    return 0;
}