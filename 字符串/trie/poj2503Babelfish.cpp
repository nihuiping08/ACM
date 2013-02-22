/*
题目：
	给出英文和密码文的互译，现在给出密码文求给出英文解析
分析：
	还是可以用字典树来构造的(当然还可以用快排+二分法，哈希函数做)，先给出trie树的构造吧
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 12
#define MAXN 100005
char ch[2*X],s1[MAXN][X],s2[X];
int cnt;
struct trie	//定义字典树的结构体
{
	bool haveend;//记录是否有单词在这结束的
	int id;		//记录当前的密文顺序
	trie *p[26];//储存26个英文字母
	trie()
	{
		haveend = false;
		id = -1;
		memset(p,NULL,sizeof(p));
	}
}root;
void insert(trie *r,char *s)//构造树的函数，把密文插入到树中
{
	int c;
	for(int i=0;s[i];i++)
	{
		c = s[i]-'a';
		if(r->p[c]==NULL)
			r->p[c] = new trie();//当前为空时，建造新的节点
		r = r->p[c];			//建造下一个节点
	}
	r->id = cnt++;				//标记顺序
	r->haveend = true;			//标记已有单词在此结束
}
int search(trie *r,char *s)
{			//查找函数
	int c;
	int len = strlen(s);
	for(int i=0;i<len;i++)//从根部开始往下走，直到该密文结束为止
	{
		c = s[i]-'a';
		if(r->p[c]==NULL)
			return -1;
		else
			r = r->p[c];
	}
	if(r->haveend)
		return r->id;
	return -1;	//不能返回0，因为0代表了第一个输入的单词
}
void seg()	//把输入的一行即分开成两个字符串
{
	bool flag = false;	//第一个字符串是否结束的标记
	int c1 = 0,c2 = 0;
	int len = strlen(ch);
	for(int i=0;i<len;i++)
	{
		if(ch[i]==' ')
			flag = true;
		if(!flag)
			s1[cnt][c1++] = ch[i];
		else if(flag&&ch[i]!=' ')
			s2[c2++] = ch[i];
	}
	s1[cnt][c1] = '\0';//一定得有结束符号
	s2[c2] = '\0';
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	trie *r = &root;
	cnt = 0;
	while(1)
	{
		gets(ch);
		if(strcmp(ch,"")==0)//输入到空行停止输入
			break;
		seg();
		insert(r,s2);
	}
	char str[X];
	while(scanf("%s",str)!=EOF)//输入要匹配的密文
	{
		int qq = search(r,str);
		if(qq==-1)	//没找到的话
			printf("eh\n");
		else
			printf("%s\n",s1[qq]);
	}
	return 0;
}