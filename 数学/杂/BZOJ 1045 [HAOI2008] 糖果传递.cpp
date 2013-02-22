/*
 *	��Ŀ��
 *		��n��С��������һȦ��ÿ����ai���ǹ���ÿ��ֻ�ܸ��������˴����ǹ���ÿ��ÿ�δ�
 *		��һ���ǹ�����Ϊ1����ʹ�����˻�þ����ǹ�����С���ۡ�
 *
 *	������
 *		����a1�ָ�an���ǹ���Ϊk������Եõ����µ���Ϣ��
 *			  a1		a2				a3		a4...		an-1  an
 *	��ǰ��Ŀ��a1-k		a2				a3		a4			an-1  an+k
 *	������ۣ�|a1-k-ave| |a1+a2-k-2*ave| |a1+a2+a3-k-3*ave|	|a1+..+a(n-1)-k-(n-1)*ave| |k|
 *	��sum[i]��ʾ��a1�ӵ�ai����i*ave�ĺ�ֵ�������Ͽ��Ի���Ϊ
 *	�ܴ��� = |s1-k|+|s2-k|+...+|s(n-1)-k|+|k|
 *	���ѿ�������kΪs1...s(n-1)�е���λ����ʱ������Ĵ�����С
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 1000005;

typedef long long ll;

ll sum[X],a[X];
ll n;

ll Abs(ll x){
	return max(x,-x);
}

int main(){
	freopen("sum.in","r",stdin);
	while(cin>>n){
		ll x;
		ll tot = 0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			tot += a[i];
		}
		
		ll ave = tot/n;
		for(int i=1;i<n;i++)
			sum[i] = a[i]+sum[i-1]-ave;
		sort(sum+1,sum+n);
		
		ll mid = sum[n/2];
		ll ans = Abs(mid);
		
		for(int i=1;i<n;i++)
			ans += Abs(sum[i]-mid);
		cout<<ans<<endl;
	}
	return 0;
}
