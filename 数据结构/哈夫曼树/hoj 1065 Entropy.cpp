/*
	HUFFMAN树,是数据结构中很基础的东西了,以前写过求HUFFMAN编码的程序,
	但是感觉这题没有必要把HUFFMAN全部球出来,一种不错的解法,是使用优先队列来解的.
	另外优先队列priority_queue是STL库中的,包含在头文件<queue>中,会自动对新放入队列的数据进行排序,
	这里采用的是队头数最小的排序方式.每次取出前两个(也就是权值最小的两节点)构成新的节点,再放入队
	列中,直到取到最后一个为止,这也符合HUFFMAN树的构造过程..

*/
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
string s;
int d[27];
//int cmp(const void *a,const void *b);
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(getline(cin,s),s!="END")
	{
		memset(d,0,sizeof(d));
		int len = s.size();
		int worst = len<<3;		//利用移位运算更快
		priority_queue<int ,vector<int>,greater<int> > q;
		//注意这里的是> >，而不是>>，>>是一个符号，PE4次
		//对字符数组排序并将字符个数依次放入优先队列中 
		sort(s.begin(),s.end());	//对字符串中的字母排序
		char ch = s[0];
		int times = 0;
		for(int i=0;i<len;i++)		//统计每个字母分别的出现次数
		{
			if(s[i]==ch)
				times++;
			else
			{
				q.push(times);
				ch = s[i];
				times = 1;
			}
		}
		q.push(times);

		//构造Huffman树的过程  
		int ans = 0,a,b;
		if(q.size()==1)
			ans = q.top();
		while(true)
		{
			a = q.top();	//找到优先队列中最小的一个数
			q.pop();
			if(q.empty())	//如果此时为空，即可退出当前循环
				break;
			b = q.top();	//找到优先队列中的最小一个数(注意之前的最小的数已经出队)
			q.pop();
			ans += a+b;
			q.push(a+b);		//把两个数合并为同一棵树
		}
		printf("%d %d %.1lf\n",worst,ans,worst*1.0/ans);
	}
	return 0;
}

