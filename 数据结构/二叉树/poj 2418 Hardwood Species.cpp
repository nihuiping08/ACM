/*
��Ŀ��
	����һЩ��������ÿһ��������ռ�ı���
������
	���Ǹ������ֵ������򣬲����������ռ�ı��������ڱ����漰�������Ƚ϶࣬���Բ���
	����������������Ȼ���������������
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 50
int cnt;
struct node	//���Ľṹ��
{
	int id;			//���������
	char name[X];	//��������
	node *rchild;	//������
	node *lchild;	//������
};
char in[X];
struct node *insert(node *r,char in[X],int len)//��������
{
	if(r==NULL)		//����ǰλ��Ϊ��ʱ��ֱ�Ӳ��뵽��λ�ü���
	{
		r = new node;	//�����µĽڵ�
		strcpy(r->name,in);//�Ѹ��������浽�ṹ���������
		r->id = 1;		//��Ϊ����һ���µ�����������ʱ������ĿΪ1
		r->lchild = NULL;//���������ÿ�
		r->rchild = NULL;
	}
	else
	{
		if(strcmp(r->name,in)>0)	//�Ƚڵ���ֵ���Сʱ���ݹ���뵽��������
			r->lchild = insert(r->lchild,in,len);
		else if(strcmp(r->name,in)<0)	//�Ƚڵ���ֵ����ʱ���ݹ���뵽��������
			r->rchild = insert(r->rchild,in,len);
		else	//�����ʱ��ֱ����Ŀ��һ����
			r->id++;
	}
	return r;
}
void inorder(node *r)	//�������
{
	if(r!=NULL)
	{
		inorder(r->lchild);
		printf("%s %.4lf\n",r->name,r->id*100.0/cnt);//��ӡ�����Ͱٷֱ�
		inorder(r->rchild);
	}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cnt = 0;
	node *r;
	r = NULL;
	while(gets(in))
	{
		cnt++;
		int len = strlen(in);
		r = insert(r,in,len);//����������������뵽�ṹ����
	}
	inorder(r);	//�������
	return 0;
}