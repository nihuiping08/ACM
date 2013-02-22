/*
题目：
	判断有没有两个电话号码能构成前缀关系
分析：
	动态构树果然是Time limitted，只能是用静态构树或者直接安字典序排完序后比较相邻两个是否
	能构成前缀关系。。。下面简单说说动态构树吧(应该是对的。。)
*/
/*
#include <iostream>
#include <cstdio>
using namespace std;
struct trie
{	//定义字典树
	bool end;
	bool id;
	trie *p[10];//一共十位数字
	trie()
	{
		end = false;//判断此处到根处有没有单词，有返回true
		id = false;//判断是否已有单词在用过从此处回到根的这些号码
		for(int i=0;i<10;i++)//开始时没有号码，置NULL
			p[i] = NULL;
	}
}root;

bool make_tree(struct trie *r,char *s)
{	//动态构树函数
	for(int i=0;s[i];i++)
	{
		if(r->p[s[i]-'0']==NULL)//如果此前没有用过此处的号码，即没有前缀关系
			r->p[s[i]-'0'] = new trie();
		else if(r->end)	//如果这个位置已有号码且该号码在此处结尾，返回false
			return false;
		r->id = true;//标记此处已经有了号码走过
		r = r->p[s[i]-'0'];
		if(r->end)	//如果这个位置已有号码且该号码在此处结尾，返回false
			return false;
	}
	if(r->id==1||r->end)//此处已有号码在此结尾或者当前号码是别人的前缀
		return false;
	r->id = true;//标记此处已经有了号码走过
	r->end = true;//标记此处已经有了号码在此结尾
	return true;
}

int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,n;
	char s[12];
	cin>>t;
	while(t--)
	{
		struct trie qq;
		int flag = 0;//标记有没有找到有前缀关系
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%s",s);
			if(!flag&&!make_tree(&qq,s))
				flag = 1;
		}
		if(flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
*/
/*
可以直接用快排函数排完序后比较前后两个是否构成前缀关系
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;
#define X 10005
string s[X];
int cmp(string s1,string s2)//快排内部比较函数
{
	return s1<s2;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			cin>>s[i];
		sort(s,s+n,cmp);//直接排序
		bool flag = 0;
		int i,j;
		for(i=0;i<n-1;i++)
		{
			int len = s[i].size();
			for(j=0;j<len;j++)
				if(s[i][j]!=s[i+1][j])//如果遇到不等时，即不能构成前缀关系
					break;
			if(j==len)//表示可以构成前缀关系
			{
				flag = true;
				break;
			}
		}
		if(flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
}