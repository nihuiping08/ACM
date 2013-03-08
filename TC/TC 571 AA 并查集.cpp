/*

题目：给出一个字符串S，现在要使得前K个字符跟后K个字符一样。可以改变某些字符，问最少需要改变多少个。
分析：把相关的放进一个集合中，然后统计集合中字符数最多的就行了。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 55;

class NewArenaPassword{
public:

    int fa[MAXN];

    int find_set(int x){
        if(fa[x]!=x)
            fa[x] = find_set(fa[x]);
        return fa[x];
    }

    int minChange(string s, int k){
        int n = s.size();
        rep(i,n)
            fa[i] = i;
        rep(i,k){
        	cout<<s[i]<<" "<<s[n-k+i]<<endl;
            int x = find_set(i);
            int y = find_set(n-k+i);
            if(x!=y)
                fa[x] = y;
        }
        int sum[55][27];
        memset(sum,0,sizeof(sum));
        rep(i,n){
            int x = find_set(i);
            sum[x][ s[i]-'a' ] ++;
        }
        int ans = 0;
        rep(i,n){
            int ret = 0,cnt = 0;
            int x = find_set(i);
            rep(j,26){
                ret += sum[x][j];
                cnt = max(sum[x][j],cnt);
                sum[x][j] = 0;
            }
            ans += ret-cnt;
        }
        return ans;
    }
};
