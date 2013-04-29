/*

題目：給出ax+by+c = 0，問在區間 X1<=x<=X2,Y1<=y<=Y2中有多少種解
分析：
    對於 a = 0 || b = 0特判
    否則，擴展GCD，求出一種可能的解x0,y0，則通項公式為
    x = x0+k*b_
    y = y0-k*a_
    b_表示b/gcd(a,b)
    a_表示a/gcd(a,b)
    則判斷x,y在各自區間中的範圍，求區間的交集。
    需要注意
    左區間為正數時向上取整
    右區間為負數時向下取整

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

typedef __int64 ll;
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

void cal(ll l,ll r,ll now,ll &x,ll &y){
    if(now<0){
        now *= -1;
        l *= -1;
        r *= -1;
        swap(l,r);
    }
    x = l/now;
    y = r/now;
    if(x*now<l) x ++; // 修正
    if(y*now>r) y --;
}

void ex_gcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x = 1;
        y = 0;
    }else{
        ex_gcd( b,a%b,y,x );
        y -= x*(a/b);
    }
}

ll solve(ll a,ll b,ll c,ll X1,ll X2,ll Y1,ll Y2){
    if( !a && !b ){
        if(c)   return 0;
        return (X2-X1+1)*(Y2-Y1+1);
    }else if( !a ){
        if( c%b==0 && Y1<=c/b && c/b<=Y2 )
            return (X2-X1+1);
        return 0;
    }else if( !b ){
        if( c%a==0 && X1<=c/a && c/a<=X2 )
            return (Y2-Y1+1);
        return 0;
    }

    ll x,y;
    ll gcd = __gcd(a,b);
    if(c%gcd)   return 0;
    ex_gcd( a,b,x,y );
    c /= gcd;
    a /= gcd;
    b /= gcd;

    x *= c;
    y *= c;

    ll lx,rx,ly,ry;
    cal( X1-x,X2-x,b,lx,rx );
    cal( Y1-y,Y2-y,-a,ly,ry );
    //if(lx>rx||ly>ry)   return 0;
    lx = max(lx,ly);
    rx = min(rx,ry);

    if(lx>rx)   return 0;
    return rx-lx+1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll x1,y1,x2,y2,a,b,c;
    while(cin>>a>>b>>c){
        c *= -1;
        cin>>x1>>x2>>y1>>y2;
        if(x1>x2||y1>y2)
            puts("0");
        else
            cout<<solve(a,b,c,x1,x2,y1,y2)<<endl;
    }

	return 0;
}
