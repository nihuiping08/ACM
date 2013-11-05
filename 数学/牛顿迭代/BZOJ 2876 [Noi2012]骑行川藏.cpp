/*

题目：
    在约束∑(K_i * S_i * (V_i-V_i')^2 <= Eu下，求∑S_i / V_i的最大值

分析：
    拉格朗日乘数法。

	
设给定二元函数z=?(x,y)和附加条件φ(x,y)=0，为寻找z=?(x,y)在附加条件下的极值点，先做拉格朗日函数L(x,y)=f(x,y)+λφ(x,y)，其中λ为参数。求L(x,y)对x和y的一阶偏导数，令它们等于零，并与附加条件联立，即
L'x(x,y)=?'x(x,y)+λφ'x(x,y)=0，
L'y(x,y)=?'y(x,y)+λφ'y(x,y)=0，
φ(x,y)=0
由上述方程组解出x，y及λ，如此求得的(x,y)，就是函数z=f(x,y)在附加条件φ(x,y)=0下的可能极值点。
	
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

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 10005;
const double EPS = 1e-12;

int n;
double s[X],k[X],Vw[X],V[X],Eu;

double f(double phi){
    double ans = 0;
    rep(i,n){
        double a = 2*phi*k[i];
        double b = -a*Vw[i];
        double c = 0;
        double d = 1;

        double l = 0;
        double r = 100;
        rep(qq,100){
            double x = l+(r-l)/2;
            if(a*x*x*x + b*x*x + c*x + d>0)
                l = x;
            else
                r = x;
        }
        V[i] = (l+r)/2;
        ans += k[i]*s[i]*(V[i]-Vw[i])*(V[i]-Vw[i]);
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    while(~scanf("%d%lf",&n,&Eu)){
        double l = -1000,r = 0;
        rep(i,n)
            scanf("%lf%lf%lf",&s[i],&k[i],&Vw[i]);
        rep(i,100){ // 牛顿迭代次数
            double phi = l+(r-l)/2;
            double temp = f(phi);
            if(temp>Eu)
                r = phi;
            else
                l = phi;
        }
    }

    double ans = 0;
    rep(i,n)
        ans += s[i]/V[i];
    printf("%.8lf\n",ans);

	return 0;
}
