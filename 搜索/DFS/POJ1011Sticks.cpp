/*
(转)
	经典搜索题，黑书上的剪枝例题。
	剪枝的空间很大，剪枝前写下朴素的搜索框架（黑字部分），
	枚举原始木棍的长度及由那些小木棍组合。原始木棍长度一定是小木棍总长度的约数，因此可以减少枚举量。

    越长的木棍对后面木棍的约束力越大，因此要把小木棍排序，按木棍长度从大到小搜索，
	这样就能在尽可能靠近根的地方剪枝。
	（剪枝一）
		  如果当前木棍能恰好填满一根原始木棍，但因剩余的木棍无法组合出合法解而返回，
		  那么让我们考虑接下来的两种策略，一是用更长的木棍来代替当前木棍，显然这样总
		  长度会超过原始木棍的长度，违法。二是用更短的木棍组合来代替这根木棍，他们的
		  总长恰好是当前木棍的长度，但是由于这些替代木棍在后面的搜索中无法得到合法解，
		  当前木棍也不可能替代这些木棍组合出合法解。因为当前木棍的做的事这些替代木棍也
		  能做到。所以，当出现加上某根木棍恰好能填满一根原始木棍，但由在后面的搜索中失
		  败了，就不必考虑其他木棍了，直接退出当前的枚举。
	（剪枝二）
         显然最后一根木棍是不必搜索的，因为原始木棍长度是总木棍长度的约数。（算不上剪枝）

         考虑每根原始木棍的第一根木棍，如果当前枚举的木棍长度无法得出合法解，就不必考虑
		 下一根木棍了，当前木棍一定是作为某根原始木棍的第一根木棍的，现在不行，以后也不
		 可能得出合法解。也就是说每根原始木棍的第一根小木棍一定要成功，否则就返回。
	（剪枝四）

         剩下一个通用的剪枝就是跳过重复长度的木棍，当前木棍跟它后面木棍的无法得出合法解，
		 后面跟它一样长度的木棍也不可能得到合法解，因为后面相同长度木棍能做到的，前面这根木棍也能做到。
	（剪枝五）
         这样剪枝基本就结束了，我们发现，每种剪枝都只是加了一条语句，但剪枝效果非常明显。
		 uva307题目跟这个一模一样，当时uva的数据规模更强，许多在poj 10+MS的程序在uva 3000MS都跑不出来，
		 当时我的加上这些剪枝，我的程序在uva也能跑出靠前的成绩。  rank：38      time：0.244s

         剪枝要平衡准确性和额外花费的关系，一开始我用上下界剪枝，这个额外花费相当大，
		 每次搜索一根原始木棍都要更新从某根木棍开始到最后一根可用木棍的总长度，对于一般的
		 数据确实能跑的比没加剪枝快，但对苛刻的，第一根木棍总不成功的数据，这个剪枝就成了
		 程序的瓶颈，导致我在poj都超时了，删除后0MS， 汗~~。

*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define X 70
int len[X];
int sum,n,Min;
bool use[X];
int cmp(const void *a,const void *b)
{
	return *(int *)b-*(int *)a;
}
bool dfs(int p,int rest,int totalrest)
{
	if(totalrest==Min)
		return true;
	for(int i=p;i<n;i++)
		if(!use[i]&&len[i]<=rest)
		{
			use[i]=true;
			if(len[i]==rest)
			{
				if(dfs(1,Min,totalrest-len[i]))
					return true;
			}
			else
			{
				if(dfs(1,rest-len[i],totalrest-len[i]))
					return true;
			}
			use[i]=false;
			if(rest==len[i])
				return false;
			if(totalrest==sum)
				return false;
			if(rest==Min)
				return false;
			while(len[i+1]==len[i])
				i++;
		}
	return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);

	while(cin>>n,n)
	{
		memset(use,false,sizeof(use));
		sum = 0;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&len[i]);
			sum+=len[i];
		}
		qsort(len,n,sizeof(len[0]),cmp);
		Min = len[0];
		while(sum%Min)
			Min++;
		while(!dfs(0,Min,sum))
		{
			Min++;
			while(sum%Min)
				Min++;
		}
		cout<<Min<<endl;
	}
	return 0;
}