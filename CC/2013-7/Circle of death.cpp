/*

题目：
	给出n个点，问任意三个点组成确定的圆包含另外一个点的概率
	
分析：
	简单计算几何，先枚举三个点，判断是否能够确定圆，能确定的话，判断点是否在圆外即可

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

const int MAXN = 50;
const double EPS = 1e-8;


const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=1111;

int dcmp(double d){
    if (fabs(d)<eps)return 0;
    return d>eps?1:-1;
}

inline double sqr(double x){return x*x;}

struct point{
    double x,y;
    point(){}
    point(double _x,double _y):
    x(_x),y(_y){};
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void output()
    {
        printf("%.2f %.2f\n",x,y);
    }
    bool operator==(point a)const
    {
        return dcmp(a.x-x)==0&&dcmp(a.y-y)==0;
    }
    bool operator<(point a)const
    {
        return dcmp(a.x-x)==0?dcmp(y-a.y)<0:x<a.x;
    }

    double len()
    {
        return hypot(x,y);
    }
    double len2()
    {
        return x*x+y*y;
    }
    double distance(point p)
    {
        return hypot(x-p.x,y-p.y);
    }
    point add(point p)
    {
        return point(x+p.x,y+p.y);
    }
    point sub(point p)
    {
        return point(x-p.x,y-p.y);
    }
    point mul(double b)
    {
        return point(x*b,y*b);
    }
    point div(double b)
    {
        return point(x/b,y/b);
    }
    double dot(point p)
    {
        return x*p.x+y*p.y;
    }
    double det(point p)
    {
        return x*p.y-y*p.x;
    }
    double rad(point a,point b)
    {
        point p=*this;
        return fabs(atan2(fabs(a.sub(p).det(b.sub(p))),a.sub(p).dot(b.sub(p))));
    }
    point trunc(double r)
    {
        double l=len();
        if (!dcmp(l))return *this;
        r/=l;
        return point(x*r,y*r);
    }
    point rotleft()
    {
        return point(-y,x);
    }
    point rotright()
    {
        return point(y,-x);
    }
    point rotate(point p,double angle)//绕点p逆时针旋转angle角度
    {
        point v=this->sub(p);
        double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
}p[50];


struct line{
    point a,b;
    line(){}
    line(point _a,point _b){
        a=_a;
        b=_b;
    }
    bool operator==(line v)
    {
        return (a==v.a)&&(b==v.b);
    }
    //倾斜角angle
    line(point p,double angle)
    {
        a=p;
        if (dcmp(angle-pi/2)==0)
        {
            b=a.add(point(0,1));
        }
        else
        {
            b=a.add(point(1,tan(angle)));
        }
    }
    //ax+by+c=0
    line(double _a,double _b,double _c)
    {
        if (dcmp(_a)==0)
        {
            a=point(0,-_c/_b);
            b=point(1,-_c/_b);
        }
        else if (dcmp(_b)==0)
        {
            a=point(-_c/_a,0);
            b=point(-_c/_a,1);
        }
        else
        {
            a=point(0,-_c/_b);
            b=point(1,(-_c-_a)/_b);
        }
    }
    void input()
    {
        a.input();
        b.input();
    }
    void adjust()
    {
        if (b<a)swap(a,b);
    }
    double length()
    {
        return a.distance(b);
    }
    double angle()//直线倾斜角 0<=angle<180
    {
        double k=atan2(b.y-a.y,b.x-a.x);
        if (dcmp(k)<0)k+=pi;
        if (dcmp(k-pi)==0)k-=pi;
        return k;
    }
    //点和线段关系
    //1 在逆时针
    //2 在顺时针
    //3 平行
    int relation(point p)
    {
        int c=dcmp(p.sub(a).det(b.sub(a)));
        if (c<0)return 1;
        if (c>0)return 2;
        return 3;
    }

    bool pointonseg(point p)
    {
        return dcmp(p.sub(a).det(b.sub(a)))==0&&dcmp(p.sub(a).dot(p.sub(b)))<=0;
    }

	bool parallel(line v)
    {
        return dcmp(b.sub(a).det(v.b.sub(v.a)))==0;
    }

	//2 规范相交
    //1 非规范相交
    //0 不相交
    int segcrossseg(line v)
    {
        int d1=dcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dcmp(b.sub(a).det(v.b.sub(a)));
        int d3=dcmp(v.b.sub(v.a).det(a.sub(v.a)));
        int d4=dcmp(v.b.sub(v.a).det(b.sub(v.a)));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
        return ((d1==0&&dcmp(v.a.sub(a).dot(v.a.sub(b)))<=0)||
                (d2==0&&dcmp(v.b.sub(a).dot(v.b.sub(b)))<=0)||
                (d3==0&&dcmp(a.sub(v.a).dot(a.sub(v.b)))<=0)||
                (d4==0&&dcmp(b.sub(v.a).dot(b.sub(v.b)))<=0));
    }

	int linecrossseg(line v)//*this seg v line
    {
        int d1=dcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dcmp(b.sub(a).det(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }
    //0 平行
    //1 重合
    //2 相交
    int linecrossline(line v)
    {
        if ((*this).parallel(v))
        {
            return v.relation(a)==3;
        }
        return 2;
    }
    point crosspoint(line v)
    {
        double a1=v.b.sub(v.a).det(a.sub(v.a));
        double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }
    double dispointtoline(point p)
    {
        return fabs(p.sub(a).det(b.sub(a)))/length();
    }
    double dispointtoseg(point p)
    {
        if (dcmp(p.sub(b).dot(a.sub(b)))<0||dcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    point lineprog(point p)
    {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
    }
    point symmetrypoint(point p)
    {
        point q=lineprog(p);
        return point(2*q.x-p.x,2*q.y-p.y);
    }
};

struct circle{
    point p;
    double r;
    circle(){}
    circle(point _p,double _r):
    p(_p),r(_r){};
    circle(double x,double y,double _r):
    p(point(x,y)),r(_r){};

    circle(point a,point b,point c)//三角形的外接圆
    {
        p=line(a.add(b).div(2),a.add(b).div(2).add(b.sub(a).rotleft())).crosspoint(line(c.add(b).div(2),c.add(b).div(2).add(b.sub(c).rotleft())));
        r=p.distance(a);
    }
    void input()
    {
        p.input();
        scanf("%lf",&r);
    }
    void output()
    {
        printf("%.2lf %.2lf %.2lf\n",p.x,p.y,r);
    }
    bool operator==(circle v)
    {
        return ((p==v.p)&&dcmp(r-v.r)==0);
    }
    bool operator<(circle v)const
    {
        return ((p<v.p) || ((p==v.p)&&dcmp(r-v.r)<0));
    }
    double area()
    {
        return pi*sqr(r);
    }
    double circumference()
    {
        return 2*pi*r;
    }
    //0 圆外
    //1 圆上
    //2 圆内
    int relation(point b){
        double dst=b.distance(p);
        if (dcmp(dst-r)<0)return 2;
        if (dcmp(dst-r)==0)return 1;
        return 0;
    }
    int relationseg(line v)
    {
        double dst=v.dispointtoseg(p);
        if (dcmp(dst-r)<0)return 2;
        if (dcmp(dst-r)==0)return 1;
        return 0;
    }
};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,n;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep(i,n)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        double ans = 0;
        double cnt = 0;
        rep(i,n)
            for(int j=i+1;j<n;j++)
                for(int k=j+1;k<n;k++){
                    line a = line(p[i],p[j]);
                    line b = line(p[j],p[k]);
                    if(a.parallel(b)){
                        cnt += n-3;
                        continue;
                    }
                    circle now = circle(p[i],p[j],p[k]);
                    rep(x,n){
                        if(x==i||x==j||x==k)    continue;
                        cnt ++;
                        if( now.relation(p[x]) )
                            ans ++;
                    }
                }
        //cout<<ans<<" "<<cnt<<endl;
        printf("%.12lf\n",ans/cnt);
    }

	return 0;
}
