/*
 *	��Ŀ��
 *		˳�ӣ���������������
 *		���ӣ�������ͬ������
 *		���ӣ�������ͬ������
 *		���ƣ�m��˳�ӻ��߿��Ӽ���һ������
 *		���ڸ���3*m+1���ƣ����ܲ��ܹ����ƣ��ܹ����Ƶ��ƺŷֱ�����ǡ�����
 *
 *	������
 *		ֱ��̰�ļ�ö�ٶ��ӣ�Ȼ�������ܲ��ܹ�����
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 3005;

int a[X],n,m;
int b[X];

bool check(){
	for(int k=1;k<=n;k++){
		if(a[k]<2)
			continue;

		bool ok = true;
		
		for(int i=1;i<=n;i++)
			b[i] = a[i];
		b[k] -= 2;
		
		for(int i=1;i<=n;i++){
			if(b[i]==0)
				continue;
			b[i] %= 3;
			if(b[i]==0)
				continue;
			if(i>n-2){
				ok = false;
				break;
			}
			if(b[i+1]<b[i]||b[i+2]<b[i]){
				ok = false;
				break;
			}
			b[i+1] -= b[i];
			b[i+2] -= b[i];
			b[i] = 0;
		}
		if(ok)
			return true;
	}
	return false;
}

int main(){
	freopen("sum.in","r",stdin);
	while(cin>>n>>m){
		int tot = 3*m+1;
		int x;
		memset(a,0,sizeof(a));
		for(int i=1;i<=tot;i++){
			scanf("%d",&x);
			a[x] ++;
		}
		bool ok = false;
		for(int i=1;i<=n;i++){
			a[i] ++;
			if(check()){
				ok?printf(" "):ok = 1;
				printf("%d",i);
			}
			a[i] --;
		}
		ok?puts(""):puts("NO");
	}
	return 0;
}
