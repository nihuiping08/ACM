/*

题目：
	给出数列：1,2,3，。。。,n
	有两种操作:
	修改pos为val
	询问[l,r]中跟p互质的数的和
	
分析：
	注意到修改操作比较少，所以我们利用容斥原理先求出1到n中与p互质的个数，然后遍历一遍修改的数组，
	进行加减即可。
	注意到可能同一位置被修改两次或者以上

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
#include <complex>
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
#define lson rt<<1
#define rson rt<<1|1
#define SZ(x) x.size()

const int MAXN = 400005;

int p[MAXN],top;
bool use[MAXN];

vector<int> g;
vector<PII> vec;

void init(){
    for(int i=2;i<MAXN;i++)
        if(!use[i]){
            p[++top] = i;
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
}

int gcd(int x,int y){
    if(x==0)return y;
    if(y==0)return x;
    return gcd(y%x,x);
}

ll sol(int n,int c){
    if(!n)return 0;
    ll ans = ll(n)*(n+1)/2;
    int all = (1<<g.size())-1;
    rep1(i,all ){
        int ret = 1;
        int tot = 0;
        foreach(j,g)
            if(i>>j&1)
                ret *= g[j] , tot ++;
        ll tmp = n/ret;
        tmp = tmp*(tmp+1)/2*ret;
        if(tot&1)ans -= tmp;
        else ans += tmp;
    }
    foreach(i,vec){
        int pos = vec[i].first;
        int val = vec[i].second;
        if(pos>n)continue;
        if(gcd(pos,c)==1)ans -= pos;
        if(gcd(val,c)==1)ans += val;
    }
    return ans;
}

ll sol(int x,int y,int c){
    g.clear();
    int now = c;
    for(int i=1;p[i]<=c&&i<=top;i++)
        if(c%p[i]==0){
            g.pb(p[i]);
            while(c%p[i]==0)
                c /= p[i];
        }
    if(c>1)g.pb(c);
    return sol(y,now)-sol(x-1,now);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    init();
    int n,m,ncase,op,x,y,c,p;
    RD(ncase);
    while(ncase--){
        vec.clear();
        RD2(n,m);
        while(m--){
            RD(op);
            if(op==1){
                RD3(x,y,p);
                cout<<sol(x,y,p)<<endl;
            }else{
                RD2(x,c);
                int ok = -1;
                foreach(i,vec)
                    if(vec[i].first==x){
                        ok = i;
                        vec[i] = MP(x,c);
                        break;
                    }
                if(-1==ok)vec.pb( MP(x,c) );
            }
        }
    }

    return 0;
}
