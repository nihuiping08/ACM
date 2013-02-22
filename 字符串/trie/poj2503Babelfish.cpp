/*
��Ŀ��
	����Ӣ�ĺ������ĵĻ��룬���ڸ��������������Ӣ�Ľ���
������
	���ǿ������ֵ����������(��Ȼ�������ÿ���+���ַ�����ϣ������)���ȸ���trie���Ĺ����
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 12
#define MAXN 100005
char ch[2*X],s1[MAXN][X],s2[X];
int cnt;
struct trie	//�����ֵ����Ľṹ��
{
	bool haveend;//��¼�Ƿ��е������������
	int id;		//��¼��ǰ������˳��
	trie *p[26];//����26��Ӣ����ĸ
	trie()
	{
		haveend = false;
		id = -1;
		memset(p,NULL,sizeof(p));
	}
}root;
void insert(trie *r,char *s)//�������ĺ����������Ĳ��뵽����
{
	int c;
	for(int i=0;s[i];i++)
	{
		c = s[i]-'a';
		if(r->p[c]==NULL)
			r->p[c] = new trie();//��ǰΪ��ʱ�������µĽڵ�
		r = r->p[c];			//������һ���ڵ�
	}
	r->id = cnt++;				//���˳��
	r->haveend = true;			//������е����ڴ˽���
}
int search(trie *r,char *s)
{			//���Һ���
	int c;
	int len = strlen(s);
	for(int i=0;i<len;i++)//�Ӹ�����ʼ�����ߣ�ֱ�������Ľ���Ϊֹ
	{
		c = s[i]-'a';
		if(r->p[c]==NULL)
			return -1;
		else
			r = r->p[c];
	}
	if(r->haveend)
		return r->id;
	return -1;	//���ܷ���0����Ϊ0�����˵�һ������ĵ���
}
void seg()	//�������һ�м��ֿ��������ַ���
{
	bool flag = false;	//��һ���ַ����Ƿ�����ı��
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
	s1[cnt][c1] = '\0';//һ�����н�������
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
		if(strcmp(ch,"")==0)//���뵽����ֹͣ����
			break;
		seg();
		insert(r,s2);
	}
	char str[X];
	while(scanf("%s",str)!=EOF)//����Ҫƥ�������
	{
		int qq = search(r,str);
		if(qq==-1)	//û�ҵ��Ļ�
			printf("eh\n");
		else
			printf("%s\n",s1[qq]);
	}
	return 0;
}