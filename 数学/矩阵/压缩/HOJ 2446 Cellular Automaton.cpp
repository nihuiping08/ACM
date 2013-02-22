/*

��Ŀ��
    ��һ��������n�����ӣ�ÿ�����ӵ�ֵΪai������ø��Ӳ���d�����и��ӵĺͶ���
    mȡ��Ϊ�µ�ֵ���ʵ�k�α任�������n�����ӵ�ֵ

������
    �����׿��Թ����һ��ѭ���ľ�����������������O(n^3*logn)��TLE��
    ���ǿ���ע�⵽ѭ������a * bֻ��Ҫ����a�ĵ�һ��*b��Ȼ���������λ�����Ե�
    ����ʱ��ΪO(n^2*logn)

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

const int X = 505;

ll a[X][X],c[X][X];
ll ans[X];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int n,m,k,d;
    while(~scanf("%d%d%d%d",&n,&m,&d,&k)){
        rep(i,n)
            scanf("%lld",&ans[i]);

        rep(i,n)
            rep(j,n)
                if( (i-j+n)%n<=d || (j-i+n)%n<=d )
                    a[i][j] = 1;
                else
                    a[i][j] = 0;

        while(k>0){
            if(k&1){
                rep(i,n){
                    c[0][i] = 0;
                    rep(j,n)
                        c[0][i] += ans[j]*a[j][i];
                }
                rep(i,n)
                    ans[i] = c[0][i]%m;
            }

            rep(i,n){
                c[0][i] = 0;
                rep(j,n)
                    c[0][i] += a[0][j]*a[j][i];
            }
            rep(i,n)
                rep(j,n)
                    if(i==0)
                        a[i][j] = c[i][j]%m;
                    else
                        a[i][j] = a[i-1][(j-1+n)%n];

            k >>= 1;
        }
        rep(i,n-1)
            printf("%lld ",ans[i]);
        printf("%lld\n",ans[n-1]);
    }
	return 0;
}
