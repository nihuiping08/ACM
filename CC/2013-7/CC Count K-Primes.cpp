/*

题目：
    寻找区间[a,b]中拥有k个不同的素数因子的数的个数
分析：
    筛法+二分

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

/******** program ********************/

const int MAXN = 2e5+5;

int use[MAXN];
vector< int > vec[10];

void init(){
    for(int i=2;i<MAXN;i++)
        if(!use[i])
            for(int j=i;j<MAXN;j+=i)
                use[j] ++;
    rep(i,MAXN)
        vec[ use[i] ].pb(i);
}

int low(int k,int x,int y){
    int ans = -1;

    int l = 0;
    int r = vec[k].size()-1;

    while(l<=r){
        int mid = (l+r)>>1;
        if(vec[k][mid]>=x){
            if(vec[k][mid]<=y)
                ans = mid;
            r = mid-1;
        }else
            l = mid+1;
    }
    return ans;
}


int up(int k,int x,int y){
    int ans = -1;

    int l = 0;
    int r = vec[k].size()-1;

    while(l<=r){
        int mid = (l+r)>>1;
        if(vec[k][mid]>y)
            r = mid-1;
        else if(vec[k][mid]<=y){
            l = mid+1;
            if(vec[k][mid]>=x)
                ans = mid;
        }
    }
    return ans;
}


int cc(){
    int l,r,k;
    RD3(l,r,k);
    int x = low(k,l,r);
    if(x==-1)   return 0;
    int y = up(k,l,r);
    return y-x+1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    int ncase;
    RD(ncase);
    while(ncase--)
        cout<<cc()<<endl;

	return 0;
}
