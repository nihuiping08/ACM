/*
终于靠自己A了一道比较难的题了(n_n)
据说是减枝题，不过我的剪枝还有待提高，以下做法竟然差点time limitted（985MS）

我自己的思路：
DFS搜索题，按当前需要构造的分数值，当前分母的总乘积，已经有了的个数，上一层分母值
进行搜索，当遇到已经有了的个数等于a时，返回假，否则从上一层的分母值开始为下一个分数
进行检查是否满足条件，满足的话答案加一
*/
#include <iostream>
#include <cmath>
using namespace std;
#define X 1e-8
int p,q,a,n;
int ans;
bool dfs(double cs,int ca,int cn,int cq)
{	//当前剩余的需要构成的分数值,当前分母的总乘积，已经有了的个数，上一层分母值
	if(cn==n)
		return false;
	int flag = 0;
	for(int j=cq;j*ca<=a;j++)
	{
		if(fabs(cs-1.0/j)<X)
		{	//因为当前是成功了的，设置旗帜表示成功，返回值应为true
			ans++;
			flag = 1;
		}
		if(cs-1.0/j>0&&dfs(cs-1.0/j,ca*j,cn+1,j))
			flag = 1;	//因为当前是成功了的，设置旗帜表示成功，返回值应为true
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
