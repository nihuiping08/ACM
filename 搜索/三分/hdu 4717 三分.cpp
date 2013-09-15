/*

题目：给出n个点的起始位置以及速度矢量，问任意一个时刻使得最远的两点的距离最小。

分析：显然只有两点的话，答案满足三分性质。对于多个点，画个图分析一下，其实也满足三分性质。
	因此，先构造n*(n-1)/2个二次函数，于是三分枚举时间即可。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

#define pb push_back
#define mp make_pair
#define eps 1e-6
typedef long long ll;

struct point {
    ll x, y, vx, vy;
} p[350];

struct func {
    ll a, b, c;
} f[50000];
int m, n;
double anst, ansd;
inline void makef(point a, point b) {
    f[m].a = (a.vx-b.vx)*(a.vx-b.vx)+(a.vy-b.vy)*(a.vy-b.vy);
    f[m].b = 2*((a.x-b.x)*(a.vx-b.vx)+(a.y-b.y)*(a.vy-b.vy));
    f[m++].c = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline double foo(int x, double t) {
    return f[x].a*t*t+f[x].b*t+f[x].c;
}
inline double getd(double t) {
    double ret = -1;
    for (int i = 0; i < m; ++i) {
        double tmp = foo(i,t);
        if (tmp > ret) ret = tmp;
    }
    return ret;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("sum.in", "r", stdin);
    // freopen("cf.out", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    for (int ncase = 1; ncase <= T; ++ncase) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%I64d%I64d%I64d%I64d",&p[i].x, &p[i].y, &p[i].vx, &p[i].vy);
        m = 0;
        for (int i = 0; i < n-1; ++i)
            for (int j = i+1; j < n; ++j)
                makef(p[i], p[j]);
        double low = .0, high = 1e120;
        while(high-low>eps) {
            double mid1 = (2*low+high)/3.0;
            double mid2 = (low+2*high)/3.0;
            double tmp1 = getd(mid1);
            double tmp2 = getd(mid2);
            if (tmp1-tmp2>eps) {
                anst = mid2;
                ansd = tmp2;
                low = mid1;
            } else {
                anst = mid1;
                ansd = tmp1;
                high = mid2;
            }
        }
        printf("Case #%d: %.2lf %.2lf\n", ncase, anst, sqrt(ansd));
    }

    return 0;
}
