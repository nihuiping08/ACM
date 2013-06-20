/*

题目：给出三个圆，求一个点，这个点看三个圆的夹角相同，如果有多个，输出最大的那个
    点与圆的夹角定义为点与圆的两条切线所成的夹角大小

分析：
    模拟退火。注意评估函数用随机数好一些。。。

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

/******** program ********************/

struct Point{
    double x,y,r;
    Point(){}
    Point(double _x,double _y,double _r):x(_x),y(_y),r(_r){}
    void rd(){
        scanf("%lf%lf%lf",&x,&y,&r);
    }

}p[5];

double dis(double x,double y){
    return sqrt(x*x+y*y);
}

double dis(double x1,double y1,double x2,double y2){
    return dis(x1-x2,y1-y2);
}

double assess(double x,double y){
    double ang[5];
    rep(i,3)
        ang[i] = dis(x,y,p[i].x,p[i].y)/p[i].r;
    double dif = 0;
    rep(i,3)
        for(int j=i+1;j<3;j++)
            dif += (ang[i]-ang[j])*(ang[i]-ang[j]);
    return dif;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    double ax = 0 , ay = 0;
    rep(i,3){
        p[i].rd();
        ax += p[i].x;
        ay += p[i].y;
    }
    ax /= 3;
    ay /= 3;

    double eps = 1e-6;
    double d = 1;
    while(d>eps){
        double cur = assess(ax,ay);
        bool ok = true;
        rep(i,10){
            double r = rand();
            double now = assess( ax+cos(r)*d , ay+sin(r)*d );
            if(now<cur){
                now = cur;
                ok = false;
                ax += cos(r)*d;
                ay += sin(r)*d;
                break;
            }
        }
        if(ok)  d *= 0.85;
    }
    if(assess(ax,ay)<eps)
        printf("%.6lf %.6lf\n",ax,ay);

	return 0;
}
