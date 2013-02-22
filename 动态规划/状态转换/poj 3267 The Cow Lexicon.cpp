/*
参考别人的程序后弄明白了，看来我还是很菜啊==！

别人：
	状态定义为dp[i]，在i之前要达到合法message需要删除的最少的字符数，
	转移的时候是dp[i-1]+1和dp[i-(能匹配的字典串的长度+需要删除的字符
	串的长度)]+需要删除的字符串的长度。

自己：
	定义状态为dp[i]，dp[i]为i前的单词最少要删除的字母数，当i=i+1时，
	判断target[i]==word[j][word[j].size()-1]是否相等，即判断该单词
	与字典中的单词的最后一位是否匹配，匹配的话往前算算是否该字典中的
	单词全部出现在要求匹配单词中，如果是并且该dp小于dp[i]+1的话，转移！
	转移方程为：
	dp[i]=min(dp[i],dp[i-cnt-word[j].size()]+cnt)
	比如：(例子中的数据稍作改动)
	bronwdcodw
		bow
		milk
		whitn
		black
		brow
		farmer
	i从1开始到len(匹配的单词长度)，算的时候要把target[i-1]
		i=1:target[0] = b,找不到，故dp[1]=dp[0]+1=1;
		i=2:target[1] = r,找不到，故dp[2]=dp[1]+1=2;
		i=3:target[2] = o,找不到，故dp[3]=dp[2]+1=3;
		i=4:target[3] = n,因whitn符合，当whiltn往前匹配时，
			不能把whitn全部匹配完全，不符合,dp[4]=dp[3]+1=4;
		i=5:target[4] = w,因为bow能匹配完，且相同的字母有3个，故
			要删除的数cnt = 5-3 = 2;令mark为字典中的bow第一个匹配target的位置,
			有dp[5]=dp[mark]+2,mark = i-cnt-bow.size()=5-2-3=0;故该dp[5]=2
			比dp[4]+1=5小，但枚举到brow时，同理可数到cnt为1，比当前的dp[5] = 2小，
		........
	下面的不再一一列举了，看程序
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
{	//就像i=5时往前数有多少个不匹配
	cnt = 0;
	int a = word[j].size();
	for(int k=i-1;k>=0;k--)
	{	//从当前的位置开始往前数
		if(target[k]==word[j][a-1])
		{
			a--;
			if(!a)	//如果把该字典单词匹配完整，返回需要删除的字母数
				return cnt;
		}
		else
			cnt++;
	}
	return -1;//如果是不能匹配完的，如i=4时，应该返回-1(不能为0)
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
		{	//核心程序
			dp[i] = dp[i-1]+1;
			for(int j=0;j<n;j++)	//如果能够与字典中单词的最后一个字母匹配并且能匹配完整的话
				if(target[i-1]==word[j][word[j].size()-1]&&Remove(i,j)!=-1)
					dp[i]=min(dp[i],dp[i-cnt-word[j].size()]+cnt);//例如i=5时
		}
		cout<<dp[len]<<endl;
	}
	return 0;
}
