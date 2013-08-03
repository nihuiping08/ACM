/*

给出一个危险串，问最少删掉多少个字符使得在文本串中不包含危险串。	

ac自动机+DP。对于一个节点为危险节点，那么他的所有儿子节点均为危险节点。
所以在建立ac自动机时把危险节点处理好。
令dp[i][j]表示当前位置为i时，在ac自动机上匹配到节点j时最少需要删除的字符数。则转移方程为
Dp[i][j] = min( dp[i-1][j]+1 )
Dp[i][ ch[j][c] ] = min( dp[i-1][j] )
显然空间可以降维。

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

const int kind = 128;
const int MAXN = 1e4+5;

int dp[2][MAXN];

struct AC{
    int ch[MAXN][kind],fail[MAXN];
    int safe[MAXN]; // 安全节点
    int tot;

    void set(int x){
        Clear(ch[x]);
        safe[x] = 1;
        fail[x] = 0;
    }

    void init(){
        set(0);
        tot = 0;
    }

    int newNode(){
        set(++tot);
        return tot;
    }

    void insert(char *s){
        int r = 0;
        for(int i=0;s[i];i++){
            int c = s[i];
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
        safe[r] = 0;
    }

    void build(){
        queue<int> q;
        rep(c,kind)
            if(ch[0][c])
                q.push( ch[0][c] );

        while(!q.empty()){
            int r = q.front();
            q.pop();

            rep(c,kind){
                int x = ch[r][c];
                if(!x){
                    ch[r][c] = ch[ fail[r] ][c];
                    continue;
                }

                q.push(x);
                if(r)   fail[x] = ch[ fail[r] ][c];
                else    fail[x] = 0;

                if(!safe[ fail[x] ])
                    safe[x] = 0;
            }
        }
    }

    void run(char *t){
        int k;
        int old = 1 , now = 0;
        memset(dp[0],0x3f,sizeof(dp[0]));
        dp[0][0] = 0;
        int ans = dp[0][1];
        for(int i=0;t[i];i++){
            int c = t[i];

            swap(old,now);
            memset(dp[now],0x3f,sizeof(dp[now][0])*tot);
            rep(j,tot){
                cmin( dp[now][j],dp[old][j]+1 );
                if( safe[ k = ch[j][c] ] )
                    cmin( dp[now][k],dp[old][j] );
            }
        }
        rep(i,tot){
            //cout<<dp[now][i]<<" ";
            cmin(ans,dp[now][i]);
        }
        //cout<<endl;
        cout<<ans<<endl;
    }
}ac;

char s[MAXN],t[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~scanf("%s%s",t,s)){
        ac.init();
        ac.insert(s);
        ac.build();
        ac.run(t);
    }
	return 0;
}
