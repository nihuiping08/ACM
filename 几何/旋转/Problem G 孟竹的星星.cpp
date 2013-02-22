/*

题目：
    给出五角星的三个点，确定其余的两个点

分析：
    我们先找出最短的一条边的两个点，然后枚举一下往逆时针还是顺时针旋转，
    就能够确定五角星的中心，然后再把其中一个点绕着中心旋转一圈之后得到
    五个点的坐标，判断一下是否包含给出的三个点即可输出。。。

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define debug puts("here")

const double eps = 1e-2;

const double PI = acos(-1);
double mod;

int dcmp(double x){
    if(fabs(x)<eps)
        return 0;
    return x>0?1:-1;
}

struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}

    friend Point operator - (Point a,Point b){
        return Point(a.x-b.x , a.y-b.y);
    }
    friend Point operator + (Point a,Point b){
        return Point(a.x+b.x , a.y+b.y);
    }
    friend bool operator < (Point a,Point b){
        return a.x<b.x || (a.x==b.x&&a.y<b.y);
    }
    friend Point operator * (Point a,double d){
        return Point(a.x*d,a.y*d);
    }
    friend bool operator == (Point a,Point b){
        return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
    }
    void read(){
        scanf("%lf%lf",&x,&y);
    }
    void out(){
        printf("%.2lf %.2lf\n",x,y);
    }
}pb,pc,A,B,C;

double get_dis(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double get_dis(Point a,Point b){
    return get_dis(a-b);
}

Point rotate(Point a , double rad){ // 向量逆时针旋转rad
	return Point( a.x*cos(rad)-a.y*sin(rad) , a.x*sin(rad)+a.y*cos(rad) );
}

bool solve(double rad72,double rad54){
    Point origin = (rotate((pc-pb), rad54)*mod+pb);

    Point ans[5];
    Point now = pc;
    for(int i=0;i<5;i++){
        ans[i] = rotate(now-origin, rad72)+origin;
        now = ans[i];
    }

    bool use[6] = {false};
    sort(ans,ans+5);
    int ret = 0;
    for(int i=0;i<5;i++){
        if(A==ans[i])
            use[i] = true;
        else if(B==ans[i])
            use[i] = true;
        else if(C==ans[i])
            use[i] = true;
        else
            ret ++;
    }

    if(ret==2)
        for(int i=0;i<5;i++)
            if(!use[i])
                ans[i].out();
    return ret==2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
#endif

    int ncase;
    scanf("%d",&ncase);
    double rad54 = 54*PI/180;
    double rad72 = 72*PI/180;
    mod = sin(rad54) / sin(rad72);

    while(ncase--){
        A.read();
        B.read();
        C.read();
        double a = get_dis(B,C);
        double b = get_dis(A,C);
        double c = get_dis(A,B);
        double tmp = min(a,min(b,c));
        pb = B;
        pc = C;
        if(dcmp(b-tmp)==0)
            pb = A;
        else if(dcmp(c-tmp)==0)
            pc = A;

        if(!solve(rad72,rad54))
            solve(-rad72,-rad54);
    }
    return 0;
}
