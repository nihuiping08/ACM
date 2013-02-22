/*
 * ��Ŀ��
 *		����һ����a1...an���ʴ�1��m�����ж��ٸ����ܹ������ܱ��������е�һ������
 *
 *	������
 *		�ݳ�ԭ�����ǵ�3,6��m =18ʱ����Ҫע����Ǵ���6��������Ҫ���������k������
 *		��С�����������鿴����
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define debug puts("here")

typedef long long ll;

const int X = 105;

int size;
int di[X];

int gcd(int x,int y){
	return x==0?y:gcd(y%x,x);
}

void cal(ll n){
	ll sum = 0;
	for(int i=1;i<(1<<size);i++){
		ll s = 1;
		bool ok = false;
		for(int j=0;j<size;j++)
			if( i & (1<<j) ){
				s = s/gcd(s,di[j])*di[j];
				ok = !ok;
			}
		if(ok)
			sum += n/s;
		else
			sum -= n/s;
	}
	cout<<sum<<endl;
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("suma.txt","r",stdin);
#endif
	int ncase,m;
	cin>>ncase;
	while(ncase--){
		scanf("%d%d",&size,&m);
		for(int i=0;i<size;i++)
			scanf("%d",&di[i]);
		cal(m);
	}
	return 0;
}
