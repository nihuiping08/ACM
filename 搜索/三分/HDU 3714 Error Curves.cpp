/*

题目：
    给出n条抛物线，Si(x) = a*x^2 + b*x + c，a>=0，定义：
    f(x) = max( Si(x) )，问在[0,1000]中的最少值

分析：
    我们画个图发现，其实抛物线开口都是向上的，而f(x)也是一个凹函数，我们可以
    三分法来做

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

struct node{
    int a,b,c;
    void read(){
        scanf("%d%d%d",&a,&b,&c);
    }
    double cal(double x){
        return a*x*x + b*x + c;
    }
}p[X];

int n;

double f(double x){
    double ans = -1e50;
    rep(i,n)
        ans = max(ans,p[i].cal(x));
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int ncase;
    cin>>ncase;
    while(ncase--){
        cin >> n;
        rep(i,n)
            p[i].read();
        double l = 0;
        double r = 1000;
        rep(i,100){
            double m1 = l+(r-l)/3;
            double m2 = r-(r-l)/3;
            if(f(m1)<f(m2))
                r = m2;
            else
                l = m1;
        }
        printf("%.4lf\n",f(l));
    }

	return 0;
}
