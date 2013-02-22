/*
哈弗曼编码，比如权值为 a:1 b:1 c:2 d:3 e:5 f:6 的树
	1.开始时由最小的两个数 a:1 b:1组成一棵树
	2.接着由新的最小的两个数 2 c:2 d:3 e:5 f:6 中的 2 c:2组成新的树
	3.接着由最小的两个数 4 d:3 组成新的树
	4.接着由最小的两个数 e:5 f:6 组成一棵树
	5.接着由最小的两个数 7 11 组成一棵树（最终形成）
	6.算最小的编码总长：= 18 + 7 + 11 + 4 + 2 = 42

	2			4			7			11				18
   / \		   / \		   / \		   /  \			   /  \
  a   b		  2   c		  4   d		  e    f		  7   11
			 / \         / \						 / \  / \
			a   b       2	c						4  d  e  f
					   / \						   / \
					  a   b						  2   c
												 / \
												a   b

可以用优先队列做，优先队列每次插入都是插入到排完序后的队列数组中(可能不是很准确)，
当还没开始建树时，把出现的次数进队，当开始建树时，每次调用头两个数据a和b，然后把两个数据
相加后，再次进队，同时优先队列会进行排序，并且每次ans += a+b,最终答案即为ans
*/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;
string s;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,command;
	while(cin>>n)
	{
		priority_queue<int ,vector<int>,greater<int> > q;	//注意，此处> >是有空格的
		int worst = 0,ans = 0;
		for(int i=0;i<n;i++)
		{
			cin>>s>>command;
			worst+=command*s.size();		//最坏情况需要的空间
			q.push(command);				//把数据进队
		}
		int a,b;
		if(q.size()==1)						//当之有一个串时
			ans = q.top();
		while(true)
		{
			a = q.top();
			q.pop();
			if(q.empty())	//只剩下一个根节点，就已经构成了一棵树
				break;
			b = q.top();
			q.pop();
			ans+=a+b;		//答案
			q.push(a+b);	//把新生成的树的权值进队
		}
		cout<<worst<<" "<<ans<<endl;
	}
	return 0;
}