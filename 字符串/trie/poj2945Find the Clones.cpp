/*
原来动态构树是这么费时间的。。。20000个单词最长为20个的题，跑到了1688MS，

题目：
	题目大概是说找出相同的字符串并且统计个数。
	
分析：
	因为昨天刚学完trie树，现在练了几道，有点感觉了，其实本题应该是可以用快排直接安字典序
	进行排序，然后按前后关系来进行判断有多少个的，下面继续讲讲trie树动态构树法吧：看程序解析
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 20005
int d[X],print[X],cnt;//d表示该单词的牌号所拥有的次数，即重复的算多次，print输出数组，总不同单词数
struct trie		//构造的字典树结构体
{
	int id;
	trie *p[4];//因为只有四个英文字母，用来构造四条树枝的
	trie()
	{
		id = -1;	//记录该单词的牌号
		memset(p,NULL,sizeof(p));
	}
}root;
int insert(trie *r,char *s)
{
	int c;
	for(int i=0;s[i];i++)
	{
		if(s[i]=='A')	//先转换成数字
			c = 0;
		else if(s[i]=='G')
			c = 1;
		else if(s[i]=='T')
			c = 2;
		else
			c = 3;
		if(r->p[c]==NULL)//如果为空的话，构造新的节点
			r->p[c] = new trie();
		r = r->p[c];	//接着往下个节点走
	}
	if(r->id==-1)	//如果为新的字符串的话，给他牌号
		r->id = cnt++;
	return r->id;	//返回该字符串的牌号
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int m,n,q;
	char ch[25];
	while(scanf("%d%d",&m,&n),m||n)
	{
		memset(d,0,sizeof(d));
		cnt = 0;
		trie *r = &root;
		for(int i=0;i<m;i++)
		{
			scanf("%s",ch);
			q = insert(r,ch);	//插入到trie树中
			d[q]++;				//该牌号的数加一
		}
		memset(print,0,sizeof(print));
		for(int i=0;i<cnt;i++)//统计每个出现次数
			print[d[i]]++;
		for(int i=1;i<=m;i++)//输出每个出现的次数
			printf("%d\n",print[i]);
	}
	return 0;
}