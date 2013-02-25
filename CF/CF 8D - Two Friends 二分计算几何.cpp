/*

题目：
    平面上三个点A,B,C，起初Alice和Bob都在A点，现在Alice需要经过B点然后到达C点，而Bob直接到达C点。现在设计路线，
    使得两人的最长公共部分最长（一旦分开，以后就算再走到一起也不算）

分析：
    我们设答案为s，所以我们知道Alice和Bob分离点pos在以A为圆心，s为半径的圆上。我们发现pos明显具有单调性。
    我们可以首先二分位置，在BC的线段上的点D，然后再二分出pos在线段AD的具体位置，然后判断该位置是否符合要求就行了。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

double X1,Y1,X2,Y2,X3,Y3;
double t1,t2;

double dis(double x,double y){
    return sqrt(x*x+y*y);
}

double dis(double x1,double y1,double x2,double y2){
    return dis(x1-x2,y1-y2);
}

double solve(double x1,double y1,double x2,double y2,double t,double px,double py){
    if(dis(x1,y1,px,py)+dis(px,py,x2,y2)-dis(x1,y1,x2,y2)<=t)
        return dis(x1,y1,x2,y2)+t-dis(px,py,x2,y2);
    double l = 0,r = 1;
    rep(step,300){
        double M = (l+r)/2;
        double dx = (1-M)*x1+M*px;
        double dy = (1-M)*y1+M*py;
        double tmp = dis(x1,y1,dx,dy)+dis(dx,dy,x2,y2)-dis(x1,y1,x2,y2);
        if(tmp<=t)
            l = M;
        else
            r = M;
    }
    return l*dis(x1,y1,px,py);
}

double cc(double x,double y){
    double tmp = solve(X1,Y1,X2,Y2,t2,x,y);
    double ret = solve(X1,Y1,X3,Y3,t1,x,y);
    return min(tmp,ret);
}

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>t1>>t2){
        cin>>X1>>Y1>>X2>>Y2>>X3>>Y3;

        double tmp = dis(X1,Y1,X3,Y3)+dis(X3,Y3,X2,Y2);
        double ret = dis(X1,Y1,X2,Y2)+t2;

        double ans = 0;
        ans = max(cc(X2,Y2),cc(X3,Y3));

        if(tmp<=ret){
            printf("%.6lf\n",min(ret,tmp+t1));
            continue;
        }

        double l = 0, r = 1;
        rep(i,300){
            double M1 = (l*2+r)/3;
            double M2 = (l+r*2)/3;
            double px1 = X2*(1-M1)+X3*M1 , py1 = Y2*(1-M1)+Y3*M1;
            double px2 = X2*(1-M2)+X3*M2 , py2 = Y2*(1-M2)+Y3*M2;
            ret = cc(px1,py1);
            tmp = cc(px2,py2);
            ans = max(ans,max(ret,tmp));
            if(ret>tmp)
                r = M2;
            else
                l = M1;
        }
        printf("%.6lf\n",ans);
    }
	return 0;
}
