/*

題目：
    給出一個圖，圖中所有的環的長度不大於3，現在需要分組，使得每個組不在
    同一個環內。
分析：
    弦圖。

    MCS算法：
    col[i]表示點i與col[i]個已經遍歷過的點存在邊，即它不能用的顏色數。
    找所有沒有遍歷過的點當中最大的col值的點。
    從一個點出發，相鄰並且沒有遍歷過的 col[y] ++。
    重複n次，max(col[i]+1)就是答案

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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 10005;
const int MAXM = 2000005;

int po[MAXN],tol;
int col[MAXN];
bool use[MAXN];

struct node{
    int y,next;
}edge[MAXM];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,n,m;
    RD2(n,m);
    while(m--){
        RD2(x,y);
        add(x,y);
        add(y,x);
    }

    int ans = 0;
    rep(q,n){
        int k = 0;
        rep1(i,n) // 找沒被遍歷過的最大col值的點
            if(!use[i]&&col[i]>=col[k])
                k = i;
        use[k] = true; // 標記為已遍歷

        // 從相鄰點出發，沒被遍歷過的點的col值加一
        for(int i=po[k];i;i=edge[i].next)
            if(!use[ edge[i].y ])
                ans = max(ans,++col[ edge[i].y ] ); // 順便更新答案
    }
    cout<<ans+1<<endl;

	return 0;
}
