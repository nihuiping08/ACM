/*
���ڿ��Լ�A��һ���Ƚ��ѵ�����(n_n)
��˵�Ǽ�֦�⣬�����ҵļ�֦���д���ߣ�����������Ȼ���time limitted��985MS��

���Լ���˼·��
DFS�����⣬����ǰ��Ҫ����ķ���ֵ����ǰ��ĸ���ܳ˻����Ѿ����˵ĸ�������һ���ĸֵ
�����������������Ѿ����˵ĸ�������aʱ�����ؼ٣��������һ��ķ�ĸֵ��ʼΪ��һ������
���м���Ƿ���������������Ļ��𰸼�һ
*/
#include <iostream>
#include <cmath>
using namespace std;
#define X 1e-8
int p,q,a,n;
int ans;
bool dfs(double cs,int ca,int cn,int cq)
{	//��ǰʣ�����Ҫ���ɵķ���ֵ,��ǰ��ĸ���ܳ˻����Ѿ����˵ĸ�������һ���ĸֵ
	if(cn==n)
		return false;
	int flag = 0;
	for(int j=cq;j*ca<=a;j++)
	{
		if(fabs(cs-1.0/j)<X)
		{	//��Ϊ��ǰ�ǳɹ��˵ģ��������ı�ʾ�ɹ�������ֵӦΪtrue
			ans++;
			flag = 1;
		}
		if(cs-1.0/j>0&&dfs(cs-1.0/j,ca*j,cn+1,j))
			flag = 1;	//��Ϊ��ǰ�ǳɹ��˵ģ��������ı�ʾ�ɹ�������ֵӦΪtrue
	}
	if(flag)
		return true;
	else
		return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>p>>q>>a>>n,p||q||a||n)
	{
		ans = 0;
		dfs(p*1.0/q,1,0,1);
		cout<<ans<<endl;
	}
	return 0;
}
