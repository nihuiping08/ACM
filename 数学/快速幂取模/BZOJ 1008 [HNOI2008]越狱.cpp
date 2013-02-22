/*

��Ŀ��
	�������������Ϊ1...N��N�����䣬ÿ�������Ѻһ�����ˣ���M���ڽ̣�ÿ�����˿�����������һ�֡�
	������ڷ���ķ��˵��ڽ���ͬ���Ϳ��ܷ���Խ�������ж�����״̬���ܷ���Խ��

������
	���ǿ����������ڵĶ���ͬ�������� = m^n - (m-1)^(n-1)*m������ֱ�ӿ������󼴿�
	
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
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 1000005;
const ll mod = 100003;

ll a[X];

ll pw(ll a,ll b){
    ll ret = 1;
    while(b>0){
        if(b&1)
            ret = (ret*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return ret;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll n,m;
    while(cin>>m>>n){
        ll x = pw(m,n);
        ll y = pw(m-1,n-1);
        y = y*m%mod;
        cout<<(x+mod-y)%mod<<endl;
    }

	return 0;
}
