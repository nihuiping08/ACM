/*
 *	分析：
 *		裸的高斯消元题
 *		二维平面上的圆上的点与圆心的距离有(x-a)^2+(y-b)^2 = r^2
 *		三维空间上的球上的点与球心的距离有(x-a)^2+(y-b)^2+(z-c)^2 = r^2
 *		同理：在n维空间上的球上的点与球心的距离有sigma((xi-ai)^2) = r^2，圆心为(a1,a2,...,an)
 *
 *		另外，在二维平面上，可由三点（不共线）确定一个园，在三维上四点（不共线）确定一个球，
 *		同理，在n维平面上，可由n+1个点（不共线）确定一个n维的球。
 *		
 *		这样，题目就可以转化为n+1个方程组，但是是平方级别的，如何转化为一维的？
 *		我们不妨对于相邻的两个方程组左右分别相减，可以发现：
 *		2*(x21 - x11)*x1 + 2*(x22 - x12)*x2 +...+2*(x2n - x1n) = (x21^2 - x11^1)+...+(x2n^2 - x1n^2)
 *		这样，由n+1个方程组就可以转化为了n个一维的方程组了。下面，直接用高斯消元法即可解决该问题
 *		
 * */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int X = 20;
#define esp 1e-8

double dp[X][X];
double a[X][X],b[X][X];
double f[X];
int n;

double gauss(){
	for(int i=1;i<=n;i++){
		int x = i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i]-a[x][i])>esp)
				x = j;
		if(x!=i)
			for(int j=1;j<=n+1;j++)
				swap(a[i][j],a[x][j]);
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>esp){
				double temp = a[j][i] / a[i][i];
				for(int k=i;k<=n+1;k++)
					a[j][k] -= temp*a[i][k];
			}
	}
	for(int i=n;i;i--){
		double temp = a[i][n+1];
		for(int j=i+1;j<=n;j++)
			temp -= f[j]*a[i][j];
		f[i] = temp / a[i][i];
	}
}

int main(){
	cin>>n;
	for(int i=1;i<n+2;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&b[i][j]);
	for(int i=1;i<=n;i++){
		double temp = 0;
		for(int j=1;j<=n;j++){
			temp += b[i+1][j]*b[i+1][j]-b[i][j]*b[i][j];
			a[i][j] = 2*(b[i+1][j]-b[i][j]);
		}
		a[i][n+1] = temp;
	}
	gauss();
	for(int i=1;i<n;i++)
		printf("%.3lf ",f[i]);
	printf("%.3lf\n",f[n]);
	return 0;
}
