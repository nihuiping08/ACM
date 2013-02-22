/*

��Ŀ��
    ����n�������ߣ�Si(x) = a*x^2 + b*x + c��a>=0�����壺
    f(x) = max( Si(x) )������[0,1000]�е�����ֵ

������
    ���ǻ���ͼ���֣���ʵ�����߿��ڶ������ϵģ���f(x)Ҳ��һ�������������ǿ���
    ���ַ�����

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
