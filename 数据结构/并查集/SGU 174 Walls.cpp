/*

Hash + 并查集

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 400005;

int fa[MAXN],n,m;

struct node{
    int x,y;
    friend bool operator < (node a,node b){
        return a.x<b.x || (a.x==b.x&&a.y<b.y);
    }
    friend bool operator == (node a,node b){
        return a.x==b.x && a.y==b.y;
    }
    void out(){
        cout<<"idx  "<<x<<" "<<y<<endl;
    }
}ha[MAXN],in[2][MAXN];

int find_set(int x){
    if(x!=fa[x])
        fa[x] = find_set(fa[x]);
    return fa[x];
}

int bin(node now){
    int l = 0 , r = n-1;
    while(l<=r){
        int mid = (l+r)/2;
        if( ha[mid]<now )
            l = mid+1;
        else if(ha[mid]==now)
            return mid;
        else
            r = mid-1;
    }
    while(true)
        ;
    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(m);
    n = 0;
    rep(i,m){
        RD2(in[0][i].x,in[0][i].y);
        RD2(in[1][i].x,in[1][i].y);
        ha[n++] = in[0][i];
        ha[n++] = in[1][i];
    }
    sort(ha,ha+n);
    int t = n;
    n = 1;
    for(int i=1;i<t;i++)
        if( !(ha[i]==ha[i-1]) )
            ha[n++] = ha[i];

    rep(i,n)
        fa[i] = i;

    rep(i,m){
        int x = bin(in[0][i]);
        int y = bin(in[1][i]);
        x = find_set(x);
        y = find_set(y);
        //in[0][i].out();
        //in[1][i].out();
        //cout<<x<<" "<<y<<endl;
        if(x==y){
            cout<<i+1<<endl;
            return 0;
        }
        fa[x] = y;
    }
    puts("0");

	return 0;
}
