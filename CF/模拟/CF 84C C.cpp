/*

给出n个靶子，射击m次，问所有靶子第一次射中时是在第几次射击中	

由于靶子横坐标满足二分性质，所以对于第i次射击，二分出他所在的第几个靶子，然后小范围内枚举。

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

const int MAXN = 2e5+5;

struct node{
    int x,r,id;
    friend bool operator < (node a,node b){
        return a.x<b.x;
    }
    void od(){
        cout<<x<<" "<<r<<" "<<id<<endl;
    }
    node(){}
    node(int i,int j,int k):x(i),r(j),id(k){}
};

vector<node> vec;
vector<node> shot;
int ans[MAXN];

bool hit(int x,int y,int o,int r){
    return r*r>=(x-o)*(x-o)+y*y;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(~RD(n)){
        vec.clear();
        shot.clear();
        int x,y;

        rep1(i,n){
            RD2(x,y);
            vec.pb(node(x,y,i));
        }
        sort(All(vec));

        memset(ans,-1,sizeof(ans));
        int len = vec.size()-1;
        RD(m);
        rep1(i,m){
            RD2(x,y);
            int now = -1;
            int l = 0;
            int r = len;
            while(l<=r){
                int mid = (l+r)/2;
                if(vec[mid].x-vec[mid].r<=x&&x<=vec[mid].x+vec[mid].r){
                    now = mid;
                    break;
                }
                if(vec[mid].x-vec[mid].r>x)
                    r = mid-1;
                else
                    l = mid+1;
            }
            if(now!=-1){
                for(int j=max(0,now-10);j<=min(now+10,len);j++){
                    if(hit(x,y,vec[j].x,vec[j].r)){
                        int id = vec[j].id;
                        if(ans[id]==-1)
                            ans[id] = i;
                    }
                }
            }
        }
        int sum = 0;
        rep1(i,n)
            sum += ans[i]!=-1;
        cout<<sum<<endl;
        rep1(i,n)
            printf("%d ",ans[i]);
        puts("");
    }

	return 0;
}
