/*
�ο����˵ĳ����Ū�����ˣ������һ��Ǻܲ˰�==��

���ˣ�
	״̬����Ϊdp[i]����i֮ǰҪ�ﵽ�Ϸ�message��Ҫɾ�������ٵ��ַ�����
	ת�Ƶ�ʱ����dp[i-1]+1��dp[i-(��ƥ����ֵ䴮�ĳ���+��Ҫɾ�����ַ�
	���ĳ���)]+��Ҫɾ�����ַ����ĳ��ȡ�

�Լ���
	����״̬Ϊdp[i]��dp[i]Ϊiǰ�ĵ�������Ҫɾ������ĸ������i=i+1ʱ��
	�ж�target[i]==word[j][word[j].size()-1]�Ƿ���ȣ����жϸõ���
	���ֵ��еĵ��ʵ����һλ�Ƿ�ƥ�䣬ƥ��Ļ���ǰ�����Ƿ���ֵ��е�
	����ȫ��������Ҫ��ƥ�䵥���У�����ǲ��Ҹ�dpС��dp[i]+1�Ļ���ת�ƣ�
	ת�Ʒ���Ϊ��
	dp[i]=min(dp[i],dp[i-cnt-word[j].size()]+cnt)
	���磺(�����е����������Ķ�)
	bronwdcodw
		bow
		milk
		whitn
		black
		brow
		farmer
	i��1��ʼ��len(ƥ��ĵ��ʳ���)�����ʱ��Ҫ��target[i-1]
		i=1:target[0] = b,�Ҳ�������dp[1]=dp[0]+1=1;
		i=2:target[1] = r,�Ҳ�������dp[2]=dp[1]+1=2;
		i=3:target[2] = o,�Ҳ�������dp[3]=dp[2]+1=3;
		i=4:target[3] = n,��whitn���ϣ���whiltn��ǰƥ��ʱ��
			���ܰ�whitnȫ��ƥ����ȫ��������,dp[4]=dp[3]+1=4;
		i=5:target[4] = w,��Ϊbow��ƥ���꣬����ͬ����ĸ��3������
			Ҫɾ������cnt = 5-3 = 2;��markΪ�ֵ��е�bow��һ��ƥ��target��λ��,
			��dp[5]=dp[mark]+2,mark = i-cnt-bow.size()=5-2-3=0;�ʸ�dp[5]=2
			��dp[4]+1=5С����ö�ٵ�browʱ��ͬ�������cntΪ1���ȵ�ǰ��dp[5] = 2С��
		........
	����Ĳ���һһ�о��ˣ�������
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
string target,word[601];
int dp[601];
int cnt;
int len,n;
int Remove(int i,int j)
{	//����i=5ʱ��ǰ���ж��ٸ���ƥ��
	cnt = 0;
	int a = word[j].size();
	for(int k=i-1;k>=0;k--)
	{	//�ӵ�ǰ��λ�ÿ�ʼ��ǰ��
		if(target[k]==word[j][a-1])
		{
			a--;
			if(!a)	//����Ѹ��ֵ䵥��ƥ��������������Ҫɾ������ĸ��
				return cnt;
		}
		else
			cnt++;
	}
	return -1;//����ǲ���ƥ����ģ���i=4ʱ��Ӧ�÷���-1(����Ϊ0)
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);

	while(cin>>n>>len)
	{
		cin>>target;
		for(int i=0;i<n;i++)
			cin>>word[i];
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=len;i++)
		{	//���ĳ���
			dp[i] = dp[i-1]+1;
			for(int j=0;j<n;j++)	//����ܹ����ֵ��е��ʵ����һ����ĸƥ�䲢����ƥ�������Ļ�
				if(target[i-1]==word[j][word[j].size()-1]&&Remove(i,j)!=-1)
					dp[i]=min(dp[i],dp[i-cnt-word[j].size()]+cnt);//����i=5ʱ
		}
		cout<<dp[len]<<endl;
	}
	return 0;
}
