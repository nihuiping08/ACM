/*

题目：
    现在有两种操作：
    1.把(x,y)加到凸包中
    2.问(x,y)是否在凸包中
    现在给出n个操作，对于操作二，输出

分析：
    平衡树维护极角序。

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

const double eps = 1e-8;

double ox,oy;

struct node{
    int x,y;
    double angle;
    int op;
    friend bool operator < (node a,node b){
        return a.angle-b.angle<0;
    }
    inline void rd(){
        scanf("%d%d%d",&op,&x,&y);
    }
    inline void ch(){
        angle = atan2(y-oy,x-ox);
    }
    inline void od(){
        cout<<op<<" "<<x<<" "<<y<<" "<<atan2(y,x)<<endl;
    }
};

set<node> s;

inline node getPre(node now){ // 得到前驱
    if(s.count(now)>0)
        return now;
    set<node>::iterator it = s.lower_bound(now );
    if(it==s.begin())
        it = s.end();
    return *--it;
}

inline node getNext(node now){ // 得到后继
    set<node>::iterator it = s.upper_bound( now );
    if(it==s.end())
        it = s.begin();
    return *it;
}

inline ll det(node a,node b,node o){
    return ll(a.x-o.x)*(b.y-o.y)-ll(b.x-o.x)*(a.y-o.y);
}

inline bool in(node now){ // 判断点是否在凸包内
    if(s.size()<3)
        return false;
    node p = getPre(now);
    node n = getNext(now);
    return det(p,n,now)>=0;
}

inline void add(node now){ // 添加
    if(in(now)) return;

    while(1){
        node n = getNext(now);
        s.erase(n);
        node nn = getNext(now);
        if(det(now,nn,n)<0){
            s.insert(n);
            break;
        }
    }

    while(1){
        node p = getPre(now);
        s.erase(p);
        node pp = getPre(now);
        if(det(pp,now,p)<0){
            s.insert(p);
            break;
        }
    }
    s.insert(now);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(~RD(n)){
        node a[5];
        ox = oy = 0;
        double t[] = {0,0.49214632134, 0.2348329743213, 0.9854827427182};
        double sum = 0;
        rep1(i,3){
            a[i].rd();
            ox += a[i].x*t[i];
            oy += a[i].y*t[i];
            sum += t[i];
        }

        s.clear();
        ox /= sum, oy /= sum;

        rep1(i,3){
            a[i].ch();
            s.insert(a[i]);
        }

        node now;
        n -= 3;
        while(n--){
            now.rd();
            now.ch();
            if(now.op==1)
                add(now);
            else
                in(now)?puts("YES"):puts("NO");
        }
    }

	return 0;
}
