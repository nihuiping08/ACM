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

const int MAXN = 60005;

struct MAX{
    int val,id;
    friend bool operator < (MAX a,MAX b){
        return a.val<b.val;
    }
    MAX(){}
    MAX(int a,int b){
        val = a;
        id = b;
    }
};

struct MIN{
    int val,id;
    friend bool operator < (MIN a,MIN b){
        return a.val>b.val;
    }
    MIN(){}
    MIN(int a,int b){
        val = a;
        id = b;
    }
};

priority_queue< MAX > qmax[33];
priority_queue< MIN > qmin[33];
int tmp[MAXN][33];
int op[MAXN];
bool ok[MAXN];
int fa[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m,a[8];
    while(cin>>n>>m){
        int sta = 1<<m;
        Clear(ok);

        rep(i,sta){
            while(!qmax[i].empty())
                qmax[i].pop();
            while(!qmin[i].empty())
                qmin[i].pop();
        }

        Clear(fa);

        int tot = 0;

        rep1(i,n){
            RD(op[i]);

            if(op[i]){
                RD(fa[i]);
                if( fa[ fa[i] ] ){
                    fa[i] = fa[ fa[i] ];
                    ok[ fa[i] ] = !ok[ fa[i] ];
                    if(ok[ fa[i] ]){
                        rep(j,sta){
                            qmax[j].push( MAX(tmp[fa[i]][j],fa[i]) );
                            qmin[j].push( MIN(tmp[fa[i]][j],fa[i]) );
                        }
                        tot ++;
                    }
                }else{
                    tot --;
                    ok[ fa[i] ] = 0;
                }

            }else{
                tot ++;

                ok[i] = true;

                rep(j,m)
                    RD(a[j]);

                rep(j,sta){
                    int t = j;
                    int s = 0;
                    rep(k,m){
                        if(t&1) s += a[k];
                        else s -= a[k];
                        t >>= 1;
                    }
                    tmp[i][j] = s;

                    qmax[j].push( MAX(s,i) );
                    qmin[j].push( MIN(s,i) );
                }
            }

            if(tot<2){
                puts("0");
                continue;
            }

            int ans = -1;
            rep(j,sta){
                MAX x;
                x.id = -1;
                int s = j;
                while(!qmax[s].empty()){
                    x = qmax[s].top();
                    if( !ok[x.id] )
                        qmax[s].pop();
                    else break;
                }

                MIN y;
                y.id = -1;
                s = j;
                while(!qmin[s].empty()){
                    y = qmin[s].top();
                    if( !ok[y.id] )
                        qmin[s].pop();
                    else
                        break;
                }

                cmax( ans,x.val-y.val );
            }

            printf("%d\n",ans);
        }
    }

	return 0;
}
