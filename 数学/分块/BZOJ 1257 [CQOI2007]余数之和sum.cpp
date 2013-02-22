/*

��Ŀ:
    ����������n��k������j(n, k)=k mod 1 + k mod 2 + k mod 3 + �� + k mod n��
    ֵ������k mod i��ʾk����i������

������
    �ֿ���㡣
    k%n = k-k/n������sum = n*m-sigma(k/i *i)
    k/i���Էֳ�����[ i,k/(k/i) )������������ڵ�����k/iֵ��ȡ����Կ��Ի���Ϊ
    һ������ĵȲ���������

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

#define debug puts("here");

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll n,k;
    while(cin>>n>>k){
        ll ans = n*k;
        if(n>k)
            n = k;
        ll j = 0;
        for(ll i=1;i<=n;i=j+1){
            j = min(n,k/(k/i));
            ans -= (j-i+1)*(j+i)*(k/i)/2;
        }
        cout<<ans<<endl;
    }

	return 0;
}
