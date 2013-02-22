/*
ԭ����̬��������ô��ʱ��ġ�����20000�������Ϊ20�����⣬�ܵ���1688MS��

��Ŀ��
	��Ŀ�����˵�ҳ���ͬ���ַ�������ͳ�Ƹ�����
	
������
	��Ϊ�����ѧ��trie�����������˼������е�о��ˣ���ʵ����Ӧ���ǿ����ÿ���ֱ�Ӱ��ֵ���
	��������Ȼ��ǰ���ϵ�������ж��ж��ٸ��ģ������������trie����̬�������ɣ����������
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 20005
int d[X],print[X],cnt;//d��ʾ�õ��ʵ��ƺ���ӵ�еĴ��������ظ������Σ�print������飬�ܲ�ͬ������
struct trie		//������ֵ����ṹ��
{
	int id;
	trie *p[4];//��Ϊֻ���ĸ�Ӣ����ĸ����������������֦��
	trie()
	{
		id = -1;	//��¼�õ��ʵ��ƺ�
		memset(p,NULL,sizeof(p));
	}
}root;
int insert(trie *r,char *s)
{
	int c;
	for(int i=0;s[i];i++)
	{
		if(s[i]=='A')	//��ת��������
			c = 0;
		else if(s[i]=='G')
			c = 1;
		else if(s[i]=='T')
			c = 2;
		else
			c = 3;
		if(r->p[c]==NULL)//���Ϊ�յĻ��������µĽڵ�
			r->p[c] = new trie();
		r = r->p[c];	//�������¸��ڵ���
	}
	if(r->id==-1)	//���Ϊ�µ��ַ����Ļ��������ƺ�
		r->id = cnt++;
	return r->id;	//���ظ��ַ������ƺ�
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
			q = insert(r,ch);	//���뵽trie����
			d[q]++;				//���ƺŵ�����һ
		}
		memset(print,0,sizeof(print));
		for(int i=0;i<cnt;i++)//ͳ��ÿ�����ִ���
			print[d[i]]++;
		for(int i=1;i<=m;i++)//���ÿ�����ֵĴ���
			printf("%d\n",print[i]);
	}
	return 0;
}