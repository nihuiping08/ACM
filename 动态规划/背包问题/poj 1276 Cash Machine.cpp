/*
������
	������Щ��Ʒ���ڶ����������������һ�����£�Ȼ����01����������⣬
	��������̫��ʱ�䣬�����time limitted�������ö�������ʽ����ӵ�ж��
	����Ʒ���������Կ�����ȫ���ұȽ�ʡʱ��
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 100005
int dp[X],cash[X];
int main()
{
	freopen("poj1276.in","r",stdin);
	freopen("poj1276.out","w",stdout);
	int total,n,a,b;
	while(cin>>total)
	{
		int cnt = 0;
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			/*for(int j=1;j<=a;j++)//ֱ����һ����̫��ʱ��
				cash[++cnt] = b;*/
			for(int j=1;j<=a;j=j*2)
			{	//���ö����Ʊ��淽ʽ�ȽϿ�Щ(��ѧ����)
				cash[++cnt] = b*j;	//�ж����Ʒ�Ĵ洢��������
				a = a-j;
			}
			if(a)	//��ʣ���
				cash[++cnt] = a*b;
		}
		///////01����������ⷽ��
		for(int j=1;j<=cnt;j++)
			for(int i=total;i>=cash[j];i--)
				dp[i] = max(dp[i],dp[i-cash[j]]+cash[j]);
		cout<<dp[total]<<endl;
	}

	return 0;
}