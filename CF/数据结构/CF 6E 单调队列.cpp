/*

维护一个子序列，使得子序列的最大最小值的差值<=k，问这个子序列的最长长度

单调队列维护最大、最小值，遇到大于k时，出队

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
#define fir first
#define sec second

/******** program ********************/

const int MAXN = 1e5+5;

int a[MAXN],n,k;

struct node{
    int id,val;
    void od(){
        cout<<id<<" "<<val<<endl;
    }
}qmax[MAXN],qmin[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>n>>k){
        ncase?puts("------------------------"):ncase = true;
        rep1(i,n)
            RD(a[i]);

        int h1 = 0 , t1 = 0 , h2 = 0 , t2 = 0;
        int ans = 0;
        vector<PII> vec;

        int p = 0;
        rep1(i,n){
            while(h1<t1&&qmax[t1].val<=a[i])
                t1 --;
            while(h2<t2&&qmin[t2].val>=a[i])
                t2 --;

            qmax[++t1].id = i;
            qmax[t1].val = a[i];

            qmin[++t2].id = i;
            qmin[t2].val = a[i];

            while(h1<t1&&h2<t2){
                if(qmax[h1+1].val-qmin[h2+1].val>k){
                    if(qmax[h1+1].id>qmin[h2+1].id){
                        h2 ++;
                        p = qmin[h2].id;
                    }
                    else{
                        h1 ++;
                        p = qmax[h1].id;
                    }
                }else   break;
            }

            //cout<<"p  =  "<<p<<endl;
            if(ans<i-p){
                ans = i-p;
                vec.clear();
                vec.pb( MP(p,i) );
            }else if(ans==i-p)
                vec.pb( MP(p,i) );
            /*
            puts("--------- qmax --------------");
            REP(j,h1+1,t1)
                qmax[j].od();
            puts("--------- qmin --------------");
            REP(j,h2+1,t2)
                qmin[j].od();
            */
        }

        //puts("--------- ansansansansans --------------");
        cout<<ans<<" "<<vec.size()<<endl;
        foreach(i,vec)
            cout<<vec[i].fir+1<<" "<<vec[i].sec<<endl;
    }

	return 0;
}
