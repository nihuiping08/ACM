/*

题目：
	先给出三个点，保证三个点不共线。
	现在添加k个点，问添加第i个点时，现有的点所形成的凸包面积的两倍
	
分析：
	动态凸包添加点计算面积的问题。
	我们先判断点是否在凸包内。
	不在的话，把三角形(next,pre,now)加上。
	然后对于上半部分，判断next是否需要删掉，需要删掉的话，面积加上三角形(next,next_next,now)，
	继续判断下一个点。
	对于下半部分进行同样的操作即可。
	
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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>

/******** program ********************/

ll area;

struct node{
    ll x,y;
    double ang;

    node(){}
    node(ll _x,ll _y):x(_x),y(_y){}
    node(ll _x,ll _y,double _a):x(_x),y(_y),ang(_a){}

    void rd(){
        int _x,_y;
        RD2(_x,_y);
        x = _x;
        y = _y;
    }

    void od(){
        cout<<x<<" "<<y<<" "<<ang<<endl;
    }

    friend bool operator < (node a,node b){
        return a.ang<b.ang;
    }

    friend node operator - (node a,node b){
        return node(a.x-b.x,a.y-b.y);
    }
};

set<node> s;

ll det(node a,node b){
    return a.x*b.y-a.y*b.x;
}

ll det(node a,node b,node o){
    return det(a-o,b-o);
}

node getPre(node now){
    if(s.count(now)>0)
        return now;
    set<node>::iterator it = s.lower_bound(now);
    if(it==s.begin())
        it = s.end();
    return *--it;
}

node getNext(node now){
    set<node>::iterator it = s.upper_bound(now);
    if(it==s.end())
        it = s.begin();
    return *it;
}

bool in(node now){
    node p = getPre(now);
    node n = getNext(now);
    return det(now,n,p)<=0;
}

void add(node now){
    if(in(now)) return;
    area += abs( det(now,getNext(now),getPre(now)) );
    while(true){
        node p = getPre(now);
        s.erase(p);
        node pp = getPre(now);
        if(det(now,pp,p)>=0){
            s.insert(p);
            break;
        }
        area += abs(det(now,pp,p));
    }

    while(true){
        node n = getNext(now);
        s.erase(n);
        node nn = getNext(now);
        if(det(now,nn,n)<=0){
            s.insert(n);
            break;
        }
        area += abs(det(n,nn,now));
    }

    s.insert(now);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    node a[5];
    double t[] = {0.49214632134, 0.2348329743213, 0.9854827427182};
    double sum = 0;
    double ox = 0 , oy = 0;

    rep(i,3){
        a[i].rd();
        ox += a[i].x*t[i];
        oy += a[i].y*t[i];
        sum += t[i];
    }
    ox /= sum;
    oy /= sum;

    s.clear();
    rep(i,3)
        s.insert(node(a[i].x,a[i].y,atan2(a[i].y-oy,a[i].x-ox)));
    area = abs( det(a[0],a[1],a[2]) );

    int n;
    RD(n);
    int x,y;
    rep(i,n){
        RD2(x,y);
        add( node(x,y,atan2(y-oy,x-ox)) );
        printf("%I64d\n",area);
    }

	return 0;
}
