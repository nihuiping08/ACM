/*
 * ��Ŀ��
 *		��һ������p��ԭ��
 *
 * ������
 *		����ת��Ϊ��euler(p-1)�����忴ά���ٿơ�ԭ����
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int euler(int n){
	int ans = n;
	for(int i=2;i*i<=n;i++)
		if(n%i==0){
			ans -= ans/i;
			while(n%i==0)
				n /= i;
		}
	if(n>1)
		ans -= ans/n;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("suma.in","r",stdin);
#endif

	int n;
	while(cin>>n)
		cout<<euler(n-1)<<endl;
	return 0;
}
