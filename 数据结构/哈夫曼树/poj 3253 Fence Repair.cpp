/*
哈夫曼树的简单应用：
切割木板。切割是要花费银子，跟切割后的两块木板的长度有关系。例如最后要得到3块木板，
长度分别为8 5 8。所以原始木板为8＋5＋8＝21
 。为了使切割花费最小，先分成13 和 8两块板子，花费银子为13＋8＝21。然后13再分割为5 
 和 8，花费银子为13。因此：This would cost 21+13=34。BUT：如果先分割成16 和 5 花费21，
 16分割为8 和 8，花费16，总花费为21＋16＝37，大于34。输出最优花费。
 这样就需要用到哈夫曼树，由于只需要输出花费总和，即树的根，就无须构造树了
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,t,a,b;
	while(cin>>n)
	{
		long long ans = 0;		//要为long long型才不会WA
		priority_queue<int ,vector<int>,greater<int> > q;
		for(int i=0;i<n;i++)
		{
			cin>>t;
			q.push(t);
		}
		if(q.size()==1)
			ans = q.top();
		while(q.size()>1)
		{
			a = q.top();
			q.pop();
			b = q.top();
			q.pop();
			ans += a+b;
			q.push(a+b);
		}
		cout<<ans<<endl;
	}
	return 0;
}