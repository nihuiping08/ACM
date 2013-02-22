/*
题目:
	给出二叉树的前序遍历和中序遍历，求给出它的后序遍历
分析：
	本题是给出一个树的先序和中序，输出它的后序。可以通过递归实现。 
	举例说明 
	先序：DBACEGF 中序：ABCDEFG 
	（1）把整个7个字符作为一段，根据先序找出第一个根D，根据中序可以得出，D左边为ABC，右边为EFG。 
	（2）对D两边递归进行（1）操作。 
	（3）递归的终止条件是这一段中只有一个字符（即为叶结点） 
	根据以上可以步骤可以生成一棵树，然后递归输出后序。 


	因为前序遍历是先把所有的左子树遍历完后才开始遍历根，再遍历右子树的，
	当树如图所示时，
	前序遍历为		DBACEGF 
	中序遍历为		ABCDEFG
    因D肯定是最早的根，所以先把它放进树中，然后中序遍历中的D把它分成左右子树
	ABC(左子树)和EFG(右子树)。
	然后继续在前序遍历的下一个字母时B，同理在中序遍历中找到B的位置，则在该位置之前的
    中序遍历的元素都在B的左子树中，同理，该位置之后的都应在B的右子树或者之前的根的右子树中，  
	在B的左子树中只剩下A，即最左边的深度为2的所有边已经构造完毕，下面递归构造，同理了。。。
			D
		   / \
		  /   \
		 B     E
		/ \     \
	   /   \     \
	  A     C     G
				 /
				/
			   F

*/
#include <iostream>
#include <string>
using namespace std;
struct node
{
	node *right;
	node *left;
	char data;
};
struct node *creat(string pre,string in)
{
	node *r;
	r = NULL;
	if(pre.size())
	{
		r = new node;
		r->data = pre[0];
		int index = in.find(pre[0]);
		r->left = creat(pre.substr(1,index),in.substr(0,index));
		r->right = creat(pre.substr(index+1),in.substr(index+1));
		/*　substr()功能：从一个字符串复制一个从指定位置开始，并具有指定长度的子字符串。 
		SUBSTR(:NEW.FLAGSTATUS,17,1) 　　其中参数依次是 （ 串，开始，长度），并返回子串。
		*/
	}
	return r;
}
void postorder(node *r)
{
	if(r!=NULL)
	{
		postorder(r->left);
		postorder(r->right);
		printf("%c",r->data);
	}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	string ch,str;
	while(cin>>ch>>str)
	{
		node *r;
		r = creat(ch,str);
		postorder(r);
		cout<<endl;
	}
	return 0;
}