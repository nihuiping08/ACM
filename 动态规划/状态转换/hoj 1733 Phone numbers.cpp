#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
string s = "22233344115566070778889990";
#define X 50010
int dp[X],pre[X],len[X],p[X],L;
string a[X],in[X],b;
void change(int x)
{
	len[x] = in[x].size();
	for(int i=0;i<len[x];i++)
		a[x].push_back(s[in[x][i]-'a']);
}
bool check(int i,int j)
{
	for(int k=len[j]-1;k>=0;k--)
		if(b[i-1]==a[j][k])
			i--;
		else
			return false;
	return true;
}
void print(int x)
{
	if(p[x]>0)
	{
		print(p[x]);
		cout<<" ";
	}
	cout<<in[pre[x]];
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n;
	while(cin>>b)
	{
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>in[i];
			change(i);
		}
		memset(pre,-1,sizeof(pre));
		memset(p,-1,sizeof(p));
		L = b.size();
		memset(dp,-1,sizeof(dp));
		dp[0] = 0;
		for(int i=1;i<=L;i++)
		{
			for(int j=0;j<n;j++)
				if(len[j]<=i&&b[i-1]==a[j][len[j]-1]&&check(i,j))
				{
					if(dp[i-len[j]]==-1)
						continue;
					int x;
					if(dp[i]==-1)
						x = dp[i-len[j]]+1;
					else
						x = min(dp[i],dp[i-len[j]]+1);
					if(dp[i]!=x)
					{
						dp[i] = dp[i-len[j]]+1;
						pre[i] = j;
						p[i] = i-len[j];
					}
				}
		}
		if(dp[L]<0)
			cout<<"No solution."<<endl;
		else
		{
			//cout<<dp[L]<<endl;
			print(L);
			cout<<endl;
		}
	}
	return 0;
}