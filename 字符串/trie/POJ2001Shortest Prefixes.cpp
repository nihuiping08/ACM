/*
��Ŀ��
	��������ܹ���ǰ׺���Ҳ��������еĵ���(��û��ʱΪ�Լ�)�ĵ���
������
	��trie��������̬������Ȼ��Ӹ��ڵ㿪ʼ�����ң����ҵ�֮ǰ���Ѿ��е���
	���߸ô��ĵ����Ѿ��߹��ýڵ㣬�������£�ֱ������������������Ϊֹ
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct trie
{	//trie��
	bool haveword;//����Ƿ�������
	int num;	//��ʾ��ĿǰΪֹ�����߹��ýڵ�ĵ�����
	trie *p[26];
	trie()
	{
		haveword = false;
		num = 0;
		memset(p,NULL,sizeof(p));
	}
}root;
void insert(trie *r,char *s)
{		//�ڵ���뺯������̬����
	for(int i=0;s[i];i++)
	{
		if(r->p[s[i]-'a']==NULL)//Ϊ��ʱ
			r->p[s[i]-'a'] = new trie();
		else		//��Ϊ��ʱ�����������������ù�֮ǰ��·��
			r->p[s[i]-'a']->num++;//���ýڵ�����Ǽ�һ
		r = r->p[s[i]-'a'];	//������һ���ڵ�
	}
	r->haveword = true;
}
void find(trie *r,char *s)
{		//���Һ���
	char print[22];//�����������·���ĵ���
	int cnt = 0;
	for(int i=0;s[i];i++)//�Ӹ�����ʼ������
	{
		int c = s[i]-'a';
		if(r->p[c]->haveword||r->p[c]->num)//����ýڵ����е����ڴ˽�β���������������ù�֮ǰ��·��
			print[cnt++] = s[i];
		else	//����Ļ����˴�����������̵�·��
		{
			print[cnt++] = s[i];
			break;
		}
		r = r->p[c];
	}
	for(int i=0;i<cnt;i++)//���
		printf("%c",print[i]);
	printf("\n");
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	char ch[1001][22];//��¼����ĵ���
	int cnt = 0;
	trie *r = &root;//�������
	while(scanf("%s",ch[cnt])!=EOF)
		insert(r,ch[cnt++]);	//������ĵ��ʲ��뵽�ֵ�����
	for(int i=0;i<cnt;i++)//���Һ���
	{
		printf("%s ",ch[i]);
		find(r,ch[i]);
	}
	return 0;
}