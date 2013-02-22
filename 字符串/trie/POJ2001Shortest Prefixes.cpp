/*
题目：
	问你最短能构成前缀的且不包括已有的单词(当没有时为自己)的单词
分析：
	用trie树做，动态构树，然后从根节点开始往下找，当找到之前是已经有单词
	或者该处的单词已经走过该节点，继续往下，直到这两个条件不成立为止
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct trie
{	//trie树
	bool haveword;//标记是否已有树
	int num;	//表示到目前为止单词走过该节点的单词数
	trie *p[26];
	trie()
	{
		haveword = false;
		num = 0;
		memset(p,NULL,sizeof(p));
	}
}root;
void insert(trie *r,char *s)
{		//节点插入函数，动态构树
	for(int i=0;s[i];i++)
	{
		if(r->p[s[i]-'a']==NULL)//为空时
			r->p[s[i]-'a'] = new trie();
		else		//不为空时，即已有其它单词用过之前的路径
			r->p[s[i]-'a']->num++;//给该节点数标记加一
		r = r->p[s[i]-'a'];	//调到下一个节点
	}
	r->haveword = true;
}
void find(trie *r,char *s)
{		//查找函数
	char print[22];//最后输出的最短路径的单词
	int cnt = 0;
	for(int i=0;s[i];i++)//从根部开始往下搜
	{
		int c = s[i]-'a';
		if(r->p[c]->haveword||r->p[c]->num)//如果该节点已有单词在此结尾或者有其它单词用过之前的路径
			print[cnt++] = s[i];
		else	//否则的话，此处到根就是最短的路径
		{
			print[cnt++] = s[i];
			break;
		}
		r = r->p[c];
	}
	for(int i=0;i<cnt;i++)//输出
		printf("%c",print[i]);
	printf("\n");
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	char ch[1001][22];//记录输入的单词
	int cnt = 0;
	trie *r = &root;//构造的树
	while(scanf("%s",ch[cnt])!=EOF)
		insert(r,ch[cnt++]);	//把输入的单词插入到字典树中
	for(int i=0;i<cnt;i++)//查找函数
	{
		printf("%s ",ch[i]);
		find(r,ch[i]);
	}
	return 0;
}