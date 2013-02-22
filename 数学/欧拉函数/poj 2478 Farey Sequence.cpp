/*
 * ��Ŀ��
 *		��0<a<b<=n�У����е�������a/b�ĸ���
 *
 * ������
 *		ֱ�ӿ��Ի�����sigma( phi(n) )��Ȼ��ת��Ϊ������ŷ��������
 *		
 *		m�ļ�Լʣ��ϵ�ĸ�����Ϊ��Ϊ��(m).ͨ����Ϊŷ��������
 *		��Ȼ����(m) ����1->m����m���ʵ����ĸ�����
 *		
 *
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int X = 1000005;

typedef long long ll;

ll ans[X];
bool use[X];

void init(){
	memset(use,false,sizeof(use));
	for(int i=1;i<X;i++)
		ans[i] = i;
	for(int i=2;i<X;i++)
		if(!use[i]){
			for(int j=i;j<X;j+=i){
				use[j] = true;
				ans[j] = ans[j]/i*(i-1);
			}
		}
	ans[2] = 1;
	for(int i=3;i<X;i++)
		ans[i] += ans[i-1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.txt","r",stdin);
#endif
	int n;
	init();
	while(scanf("%d",&n),n)
		printf("%lld\n",ans[n]);

	return 0;
}

