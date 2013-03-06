/*

题目：
    d(n) = sigma(数字之和)+n。同样有d(d(n))...
    现在问在1到n中，有多少个不可以通过d(n)构造出来的数，并且要求出给出
    的第几个这样的数

分析：
    map，数组开1百万会MLE。。。
    所以只能够自己实现hash，或者用二分来做。
    我们注意到:
    当i%10!=0时，d(n) = d(n-1)+2

*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 5005;

int ha[MAXN];
int id[MAXN],top;
bool use[100];
int ans[MAXN];
int n,m,tot;

inline int cal(int x){
    int ans = x;
    while(x){
        ans += x%10;
        x /= 10;
    }
    return ans;
}

int has(int x){ // hash
    int l = 0,r = tot;
    while(l<=r){
        int mid = (l+r)>>1;
        if(ha[mid]==x)
            return mid;
        if(ha[mid]>x)
            r = mid-1;
        else
            l = mid+1;
    }
    return -1;
}

void solve(){
    int x = 0;
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(use[i%100]==0){
            cnt ++;
            int tmp = has(cnt);
            if(tmp!=-1)
                ans[ tmp ] = i;
        }
        else    // 1x可能不是，需要把它置反
            use[i%100] = 0;

        x = i%10==0?cal(i):x+2;

        use[x%100] = true;
    }
    printf("%d\n",cnt);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep(i,m){
        RD(id[i]);
        ha[i] = id[i];
    }

    sort(ha,ha+m); // hash
    for(int i=1;i<m;i++)
        if(ha[i]!=ha[i-1])
            ha[++tot] = ha[i];

    solve();
    rep(i,m){
        if(i)   putchar(' ');
        printf("%d",ans[ has(id[i]) ]);
    }
    puts("");
	return 0;
}
