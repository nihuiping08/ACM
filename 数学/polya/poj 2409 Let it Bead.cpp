/*
 * ��Ŀ��
 *		һ��������n�����ӣ���t����ɫ����������Ϳɫ����ȥ���ȼ�֮�����ӵ�Ϳɫ��Ŀ
 *
 *	������
 *		polya����ԭ��
 *		���������Ϳɫ�����������
 *		1.��ת����Ȼ��n����ת��ʽ���ֱ�Ϊ��תi����ѭ����Ϊgcd(i,n)��
 *		���ǿ��Ժ�������һ�£�
 *		1 2 3 4 5 6    1 2 3 4 5 6    1 2 3 4 5 6   1 2 3 4 5 6   1 2 3 4 5 6
 *		1 2 3 4 5 6    6 1 2 3 4 5    5 6 1 2 3 4   4 5 6 1 2 3   3 4 5 6 1 2
 *		
 *		1 2 3 4 5 6
 *		2 3 4 5 6 1
 *		���ǿ��Զ���ÿ��Ⱥ�����Էֳ�gcd(i,n)��ѭ��Ⱥ��ѭ����Ϊgcd(i,n)��
 *
 *		2.��ת��������������ۣ�
 *		 1����nΪ������ʱ����ÿ��������Ϊ��ת�ᣬ�Գ�����n�������γ��˳���Ϊ(n-1)/2
 *			 ��ѭ��������ѭ���ĸ���Ϊ(n+1)
 *		 2����nΪż����ʱ����ÿ��������Ϊ��ת�ᣬ�Գ�����n/2�������γ���n/2-1������Ϊ
 *			2��ѭ������������Ϊ1��ѭ��������������֮����Ϊ��ת�ᣬ�Գ�����n/2�������γ�
 *			n/2������Ϊ2��ѭ��
 *
 * */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll x,ll y){
	return x==0?y:gcd(y%x,x);
}

ll pw(ll x,ll sp){
	ll ans = 1;
	for(int i=0;i<sp;i++)
		ans *= x;
	return ans;
}

void polya(ll n,ll t){
	ll ans = 0;
	for(int i=1;i<=n;i++)
		ans += pw(t,gcd(i,n));
	if(n&1)
		ans += n*pw(t,(n+1)/2);
	else
		ans += n/2 * ( pw(t,n/2)+pw(t,n/2+1) );
	cout<<ans/(2*n)<<endl;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sumd.txt","r",stdin);
#endif

	ll n,t;
	while(cin>>t>>n,t||n)
		polya(n,t);
	return 0;
}

