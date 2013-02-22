/*

题目大意：Alice和Bob做博弈游戏。游戏规则：有n堆石子，两人轮流操作，Alice是先手，每次从n堆石子中，
选取一堆，取走任意多个石子（至少取走1个），然后，把这堆石子剩下的石子取一部分（可取完，也可以不取）
分配到其他堆。问，Alice是否能必胜。

思路：

当n=1时：
先手直接取完，所以先手必胜。

当n=2时：
若两堆石子相等：
先手取后只剩一堆则变为必胜局面；
先手取后依然有两堆石子，后手总可把局面变为两堆石子相等，直到1,1，所以，还是先手败。
所以，两堆石子相等，先手必败。
若两堆石子不等：
先手总能把局面变为两堆石子相等的必败局面，所以，先手必胜。

当n=3时：
a1<=a2<=a3
先手总能对a3下手，让局面变为a2,a2的必败局面，所以先手必胜。
证明：因为a3最大，只需要给a1给a2-a1那么多石子，是可行的。

根据以上发现：
当n是奇数时，先手必胜。
证明：
a1<=a2<=……<=an-1<=an
an给a1给a2-a1
an给a3给a4-a3
……
an给an-2给an-1 - an-2
an总的给出去的石子是(a2-a1)+(a4-a3)+……+(an-1 - an-2)，可发现这些差值和定小于an，可行。

当n时偶数时：
若排序后，有：a1==a2,a3==a4,……,an-1==an。显然，先手必败。
否则：
总能对an下手，把an变为a1，然后使：a2==a3,a4==a5,……,an-2==an-1.
an给出去的总石子是(a3-a2)+(a5-a4)+……+(an-1 - an-2)，可发现这些差之和定小于an-a1，可行。

即：
n为奇数，先手必胜。
n为偶数，a不配对时，先手必胜。
n为偶数，a配对时，先手必败。


*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int a[12],n;
	while(cin>>n,n)
	{
		for(int i=0;i<n;i++)
			cin>>a[i];
		if(n&1)
			cout<<1<<endl;
		else
		{
			sort(a,a+n);
			bool flag = false;
			for(int i=0;i<n;i+=2)
				if(a[i]!=a[i+1])
					flag = true;
			if(flag)
				cout<<1<<endl;
			else
				cout<<0<<endl;
		}
	}
	return 0;
}