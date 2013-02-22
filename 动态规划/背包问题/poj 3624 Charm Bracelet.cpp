/*
��Ŀ��
	������������m�������d���01�������⣬��״̬ת�Ʒ���Ϊ
	dp[i][j] = max{dp[i-1][j],dp[i-1][j-w[i]]+d[i]}
	��Ϊ״̬ת��ʱi�ı仯һ��������ѹ��dp��ֱ�ӿ�һά������
	dp[j]=max{dp[j],dp[j-w[j]]+d[j]}�����⣬��Ϊj�Ǵ�
	���濪ʼ���صݹ�ģ�����������w,d��ֱ�ӿ�ʼ����ǰ��ģ�
	�ù�������ķ������ٶ�������d[]�Ŀռ����ģ�����������£�
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 15000
int dp[X];
int main()
{
	freopen("poj3624.in","r",stdin);
	freopen("poj3624.out","w",stdout);
	int n,m,w,d;
	while(cin>>n>>m)
	{
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&w,&d);
			for(int j=m;j>=0;j--)	//���Ĵ���
				if(j>=w)
					dp[j] = max(dp[j],dp[j-w]+d);
		}
		cout<<dp[m]<<endl;
	}

	return 0;
}