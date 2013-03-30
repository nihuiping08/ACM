/*

題目：
    給出n條直線y = ax+b，給定a,b，問從y=+00處往下看，能夠看到的直線標號。
分析：
    1.先對斜率a排序，相同的需要去掉b小的直線，不然再求交點的時候會出現
    除零錯誤。
    2.維護一個棧，表示能夠看得到的直線。然後對於L_now與棧頂L_top的交點
    的橫座標比L_top與L_top-1的橫座標小或者等於的話，需要把棧頂出棧，畫
    圖就懂了。。。
    3.最後得到的棧就是答案

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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 50005;

int ans[MAXN];
int st[MAXN];

struct Line{
    int a,b;
    int id;
    friend bool operator < (Line L1,Line L2){
        return L1.a<L2.a||(L1.a==L2.a&&L1.b>L2.b);
    }
}p[MAXN];

double cal(int a1,int b1,int a2,int b2){
    return double(b2-b1)/(a1-a2);
}

double cal(Line a,Line b){
    return cal(a.a,a.b,b.a,b.b);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    RD(n);
    rep(i,n){
        RD2(p[i].a,p[i].b);
        p[i].id = i;
    }

    sort(p,p+n);
    int m = n-1;
    n = 1;
    rep1(i,m)
        if(p[i].a!=p[i-1].a)
            p[n++] = p[i];

    int top = 1;
    st[1] = 0;
    for(int i=1;i<n;i++){
        while(top>1&&cal(p[st[top]],p[st[top-1]])-cal(p[st[top]],p[i])>=0)
            -- top;
        st[++top] = i;
    }

    rep1(i,top)
        ans[i] = p[st[i]].id;
    sort(ans+1,ans+top+1);

    rep1(i,top)
        printf("%d ",ans[i]+1);
    puts("");
	return 0;
}
