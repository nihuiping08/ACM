/*
���⣺
	������ֵ�ֱ�Ϊ1��6�Ķ����ĸ��������������ܲ���ƽ����Щ����
������
	���ر������⣬��Ϊ���ݲ��������ܹ�20000����Ʒ�����Բ��ö�����ѹ��dp�ķ���
	����״̬ת�Ʒ��̺�����д����
	dp[i][j] = max(dp[i-1][j],dp[i][j-d[i]]+d[i])����Ȼ����01������˼�룬ѹ���ռ�ΪO(n)
	״̬ת�Ʒ���Ϊdp[j] = max(dp[j],dp[j-d[i]]+d[i])��
	ע�⵽��ʱ��ȫ����Ʒ��Ϊ6�Ļ�����ȻҪ��dp����120002(��ʵӦ�ÿ���ֻ����60002����)�Ų���
	PE���Ҿ͹�����һ���ˣ�������ע�⵽����ƽ�ֵĻ����ܺͱ�Ϊ2�ı���
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 120010
int d[7],dp[X],a[X],n;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int cnt = 0,temp,cur;
	while(cin>>d[1]>>d[2]>>d[3]>>d[4]>>d[5]>>d[6],d[6]||d[1]||d[2]||d[3]||d[4]||d[5])
	{
		n = 0;
		int sum = d[1]+d[2]*2+d[3]*3+d[4]*4+d[5]*5+d[6]*6;
		printf("Collection #%d:\n",++cnt);
		if(sum%2)
			cout<<"Can't be divided."<<endl<<endl;
		else
		{
			for(int i=1;i<=6;i++)
			{
				temp = 1;
				cur = d[i];
				while(cur-temp>0)	//������ѹ��
				{
					a[n++] = temp*i;
					cur-=temp;
					temp*=2;
				}
				a[n++] = cur*i;		//ע�⵽���п��ܻ�û�б�����Ŀ���
			}
			sum/=2;
			memset(dp,0,sizeof(dp));
			for(int i=0;i<n;i++)
				for(int j=sum;j>=a[i];j--)
					dp[j] = max(dp[j],dp[j-a[i]]+a[i]);
			if(dp[sum]==sum)
				printf("Can be divided.\n\n");
			else
				cout<<"Can't be divided."<<endl<<endl;
		}
	}
	return 0;
}
