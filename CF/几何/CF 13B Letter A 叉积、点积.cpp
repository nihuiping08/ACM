/*

题目：
    判断A是否书写正确。正确有三点：
    1.第一条和第二条线段端点相同。
    2.第一条和第二条线段的夹角>0 <=90
    3.第三条线段的两端点把第一二条线段分成两个部分，且该两个部分
    的最长和最短的比例<=4

分析：
    直接叉积、点积判断点是否在线段上

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

struct Point{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y):x(_x),y(_y){}

    friend bool operator == (Point a,Point b){
        return a.x==b.x && a.y==b.y;
    }

    friend Point operator - (Point a,Point b){
        return Point( a.x-b.x , a.y-b.y );
    }
    friend Point operator + (Point a,Point b){
        return Point( a.x+b.x , a.y+b.y );
    }
    friend Point operator * (Point a,ll t){
        return Point( a.x*t , a.y*t );
    }
    friend Point operator / (Point a,ll t){
        return Point( a.x/t , a.y/t );
    }

    void rd(){
        scanf("%I64d%I64d",&x,&y);
        x *= 5;
        y *= 5;
    }
    void od(){
        cout<<x<<" "<<y<<endl;
    }
    void Od(){
        cout<<x/5<<" "<<y/5<<" ";
    }
};

ll det(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
ll det(Point a,Point b,Point o){
    return det(a-o,b-o);
}

ll dis2(Point a){
    return a.x*a.x + a.y*a.y;
}
ll dis2(Point a,Point b){
    return dis2(a-b);
}

ll dot(Point a,Point b){ // 点积
	return a.x*b.x + a.y*b.y;
}
ll dot(Point a,Point b,Point o){ // 点积
	return dot(a-o,b-o);
}

bool ok(Point a,Point b,Point c){
    Point lx = (a*4+b)/5;
    Point rx = (a+b*4)/5;
    if( det(lx,rx,c)==0&&dot(lx,rx,c)<=0 )
        return true;
    return false;
}

bool cc(Point a[2],Point b[2],Point c[2]){

    if( a[0]==b[1] || a[1]==b[1] )
        swap(b[0],b[1]);

    if(a[1]==b[0])
        swap(a[0],a[1]);

    if( !(a[0]==b[0]) )
        return false;

    if( det(a[1],b[1],a[0])==0 )
        return false;

    if( dis2(a[0],a[1]) + dis2(a[0],b[1]) < dis2(a[1],b[1]) )
        return false;

    return ok(a[0],a[1],c[0])&&ok(b[0],b[1],c[1]);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);

    Point a[2],b[2],c[2];

    //int cnt = 0;

    while(ncase--){
        a[0].rd();
        a[1].rd();
        b[0].rd();
        b[1].rd();
        c[0].rd();
        c[1].rd();

        a[1] = a[1]-a[0];
        b[0] = b[0]-a[0];
        b[1] = b[1]-a[0];
        c[0] = c[0]-a[0];
        c[1] = c[1]-a[0];
        a[0] = a[0]-a[0];

        /*
        a[0].od();
        a[1].od();
        b[0].od();
        b[1].od();
        c[0].od();
        c[1].od();
        */

        if(cc(a,b,c)||cc(a,c,b)||cc(b,c,a))
            puts("YES");
        else if(cc(b,a,c)||cc(c,a,b)||cc(c,b,a))
            puts("YES");
        else
            puts("NO");

        /*
        ++cnt;
        if(cnt==7){
            puts("0 0");
            (a[1]-a[0]).od();
            (b[0]-a[0]).od();
            (b[1]-a[0]).od();
            (c[0]-a[0]).od();
            (c[1]-a[0]).od();
        }
        */

        /*
        if(++cnt>=7){
            a[0].Od();
            a[1].Od();
            b[0].Od();
            b[1].Od();
            c[0].Od();
            c[1].Od();
        }
        */

    }

	return 0;
}
