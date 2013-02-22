/*
题目：
	给出一些树名，问每一棵树的所占的比例
分析：
	就是给树按字典序排序，并输出他们所占的比例，由于本题涉及的树名比较多，可以采用
	二分搜索树来做，然后按照中序遍历即可
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 50
int cnt;
struct node	//树的结构体
{
	int id;			//储存个数的
	char name[X];	//储存名字
	node *rchild;	//右子树
	node *lchild;	//左子树
};
char in[X];
struct node *insert(node *r,char in[X],int len)//插入树名
{
	if(r==NULL)		//当当前位置为空时，直接插入到该位置即可
	{
		r = new node;	//申请新的节点
		strcpy(r->name,in);//把该树名储存到结构体的数组中
		r->id = 1;		//因为这是一棵新的树，所以暂时它的数目为1
		r->lchild = NULL;//左右子树置空
		r->rchild = NULL;
	}
	else
	{
		if(strcmp(r->name,in)>0)	//比节点的字典序小时，递归插入到左子树中
			r->lchild = insert(r->lchild,in,len);
		else if(strcmp(r->name,in)<0)	//比节点的字典序大时，递归插入到右子树中
			r->rchild = insert(r->rchild,in,len);
		else	//当相等时，直接数目加一即可
			r->id++;
	}
	return r;
}
void inorder(node *r)	//中序遍历
{
	if(r!=NULL)
	{
		inorder(r->lchild);
		printf("%s %.4lf\n",r->name,r->id*100.0/cnt);//打印树名和百分比
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
		r = insert(r,in,len);//把新输入的树名插入到结构体中
	}
	inorder(r);	//中序遍历
	return 0;
}