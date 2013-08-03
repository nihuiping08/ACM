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

const int MAXN = 1000005;

int c[MAXN],a[MAXN],n;
int po[MAXN],last[MAXN];
int ans[MAXN];
bool use[MAXN];

struct node{
    int x,y,id;
    friend bool operator < (node a,node b){
        return a.x<b.x;
    }
}q[MAXN];

int lowbit(int x){
    return x & -x;
}

void modify(int x,int val){
    if(!x)return;
    while(x<MAXN){
        c[x] += val;
        x += lowbit(x);
    }
}

int ask(int x){
    int ans = 0;
    for(;x>0;x-=lowbit(x))
        ans += c[x];
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>n){
        ncase?puts("----------------------"):ncase = 1;

        Clear(c);
        Clear(use);
        Clear(po);

        rep1(i,n){
            RD(a[i]);
            a[i] ++;
            if(use[a[i]])
                continue;
            use[a[i]] = 1;
            modify(i,1);
        }

        //cout<<ask(MAXN-1)<<endl;

        for(int i=n;i;i--){
            last[i] = po[a[i]];
            po[a[i]] = i;
        }

        int m;
        RD(m);
        rep(i,m){
            RD2(q[i].x,q[i].y);
            q[i].id = i;
        }
        sort(q,q+m);

        memset(ans,-1,sizeof(ans));
        int now = 1;

        rep(i,m){
            while(now<=n&&now<q[i].x){
                modify( now,-1 );
                modify( last[now],1 );
                //cout<<now<<" "<<last[now]<<" "<<q[i].x<<endl;
                now ++;
            }
            //cout<<"y  =  "<<q[i].y<<endl;
            ans[ q[i].id ] = ask(q[i].y);
        }
        rep(i,m)
            printf("%d\n",ans[i]);
    }

	return 0;
}
