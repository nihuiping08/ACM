/*

题目：双十字
分析：
    先预处理出每个格子能够往两边扩展的格子数，记为w[x,y]。
    我们枚举每一列，从上面往下面数。

    用数组c[x]表示向两边扩展了x的格子数目。
    用数组dl[top]表示从上往下第top个非0格子坐标。

    数到0的时候，就把dl数组清空。
    数到1的时候，放进dl数组。

    由于当前的位置为第top个非零格子。我们假设当前格子向两边扩展的格子数
    为len，则我们可以写出这样一条式子：
    (len-1)*c[1] + {(len-1)+(len-2)}*c[2]+...+{(len-1)+..+1}*c[len-1]+
    {c[len]+...+c[max_len]}*(len-1)*len/2
    我们可以进一步化简式子如下：
    len*{c[1] + 2*c[2]+...+(len-1)*c[len-1]}
    -
    { c[1]+(1+2)*c[2]+...+(1+...+(len-1)*c[len-1]) }
    +
    len*(len-1)*{c[len]+...+c[max_len]}
    然后我们用三个树状数组来统计就行了。
    每次遇到一个非零格子的时候，把答案加上前一次的统计数（下面至少需要
    一个点）

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)

const int MAXN = 2000000;
const int MOD = 1000000009;

ll w[MAXN],c[MAXN][3],s[MAXN][3];
int dl[MAXN];
bool map[MAXN];
int n,m;

int lowbit(int x){
    return x & -x;
}

void modify(int x,int d,ll val){
    if(x==0)    return;
    val = (val*s[x][d])%MOD;
    while(x<=m){
        c[x][d] = (c[x][d]+val)%MOD;
        x += lowbit(x);
    }
}

ll ask(int x,int d){
    ll ret = 0;
    while(x>0){
        ret = (ret+c[x][d])%MOD;
        x -= lowbit(x);
    }
    return ret;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,x,y;
    RD2(n,m);
    RD(ncase);
    while(ncase--){
        RD2(x,y);
        map[x*m-m+y] = true;
    }
    for(int i=1;i<=n;i++){
        int now = 1;
        for(int j=1;j<=m;j++){
            if(map[i*m-m+j])
                now = j+1;
            else
                w[i*m-m+j] = j-now;
        }
        now = m;
        for(int j=m;j;j--){
            if(map[i*m-m+j])
                now = j-1;
            else
                w[i*m-m+j] = min(w[i*m-m+j],(ll)now-j);
        }
    }

    for(int i=1;i<=m;i++){
        s[i][0] = i;
        s[i][1] = i*(i+1)>>1;
        s[i][2] = 1;
    }


    ll ans = 0,z = 0;
    int top = 0;
    for(int j=1;j<=m;j++){
        for(int k=2;k<top;k++)
            rep(d,3)
                modify( w[dl[k]],d,-k+1 );
        top = 0,z = 0;
        for(int i=1;i<=n;i++){
            if(map[i*m-m+j]){
                for(int k=2;k<top;k++)
                    rep(d,3)
                        modify( w[dl[k]],d,-k+1 );
                top = 0,z = 0;
            }else{
                ans = (ans+z)%MOD;
                ll now = dl[++top] = i*m-m+j;
                if(w[now]>1){
                    ll tmp = w[now]*ask(w[now]-1,0)%MOD;
                    tmp = (tmp-ask(w[now]-1,1))%MOD;
                    ll ret = w[now]*(w[now]-1)%MOD;
                    ret = (ret*(ask(m,2)-ask(w[now]-1,2))>>1)%MOD;
                    tmp = (tmp+ret)%MOD;
                    z = (z+tmp)%MOD;
                }
                if(top>2&&w[dl[top-1]]>0)
                    rep(d,3)
                        modify(w[dl[top-1]],d,top-2);
            }
        }
    }

    cout<<(ans+MOD)%MOD<<endl;

	return 0;
}

