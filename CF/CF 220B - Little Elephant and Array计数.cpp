/*

题目：
    给出n个数，然后询问区间[l,r]中满足若数x出现过的次数至少为x的数的个数

分析:
    由于题目n的范围为1e5，所以最多只有450个数左右符合条件，首先把不符合条件
    的删除，得到新的序列，然后可以用dp[i][j]先预处理出位置j中出现过了标号为
    i的数的个数

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 500;
const int maxm = 100005;

int a[maxm],b[maxm],c[maxm][2],n,m;
int dp[maxn][maxm];
vector<int> v;

int main(){
    //freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[i] = a[i];
        }

        sort(a+1,a+n+1);
        a[0] = -1;
        v.clear();
        int cnt = 0;

        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            if(a[i]!=a[i-1])
                cnt++;
            c[cnt][0] = a[i];
            c[cnt][1]++;
        }
        for(int i=1;i<=cnt;i++)
            if(c[i][1]>=c[i][0])
                v.push_back(c[i][0]);

        int len = v.size();
        memset(dp,0,sizeof(dp));
        for(int i=0;i<len;i++){
            for(int j=1;j<=n;j++)
                if(v[i]==b[j])
                    dp[i][j] = dp[i][j-1]+1;
                else
                    dp[i][j] = dp[i][j-1];
        }
        int x,y;
        while(m--){
            scanf("%d%d",&x,&y);
            int ans = 0;
            for(int i=0;i<len;i++)
                ans += (dp[i][y]-dp[i][x-1])==v[i];
            printf("%d\n",ans);
        }
    }
    return 0;
}
