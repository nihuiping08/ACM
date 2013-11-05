/*

��Ŀ��
    ��Լ����(K_i * S_i * (V_i-V_i')^2 <= Eu�£����S_i / V_i�����ֵ

������
    �������ճ�������

	
�������Ԫ����z=?(x,y)�͸���������(x,y)=0��ΪѰ��z=?(x,y)�ڸ��������µļ�ֵ�㣬�����������պ���L(x,y)=f(x,y)+�˦�(x,y)�����Ц�Ϊ��������L(x,y)��x��y��һ��ƫ�����������ǵ����㣬���븽��������������
L'x(x,y)=?'x(x,y)+�˦�'x(x,y)=0��
L'y(x,y)=?'y(x,y)+�˦�'y(x,y)=0��
��(x,y)=0
��������������x��y���ˣ������õ�(x,y)�����Ǻ���z=f(x,y)�ڸ���������(x,y)=0�µĿ��ܼ�ֵ�㡣
	
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
        rep(i,100){ // ţ�ٵ�������
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
