/*
��Ŀ:
	������������ǰ������������������������ĺ������
������
	�����Ǹ���һ���������������������ĺ��򡣿���ͨ���ݹ�ʵ�֡� 
	����˵�� 
	����DBACEGF ����ABCDEFG 
	��1��������7���ַ���Ϊһ�Σ����������ҳ���һ����D������������Եó���D���ΪABC���ұ�ΪEFG�� 
	��2����D���ߵݹ���У�1�������� 
	��3���ݹ����ֹ��������һ����ֻ��һ���ַ�����ΪҶ��㣩 
	�������Ͽ��Բ����������һ������Ȼ��ݹ�������� 


	��Ϊǰ��������Ȱ����е��������������ſ�ʼ���������ٱ����������ģ�
	������ͼ��ʾʱ��
	ǰ�����Ϊ		DBACEGF 
	�������Ϊ		ABCDEFG
    ��D�϶�������ĸ��������Ȱ����Ž����У�Ȼ����������е�D�����ֳ���������
	ABC(������)��EFG(������)��
	Ȼ�������ǰ���������һ����ĸʱB��ͬ��������������ҵ�B��λ�ã����ڸ�λ��֮ǰ��
    ���������Ԫ�ض���B���������У�ͬ����λ��֮��Ķ�Ӧ��B������������֮ǰ�ĸ����������У�  
	��B����������ֻʣ��A��������ߵ����Ϊ2�����б��Ѿ�������ϣ�����ݹ鹹�죬ͬ���ˡ�����
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
		/*��substr()���ܣ���һ���ַ�������һ����ָ��λ�ÿ�ʼ��������ָ�����ȵ����ַ����� 
		SUBSTR(:NEW.FLAGSTATUS,17,1) �������в��������� �� ������ʼ�����ȣ����������Ӵ���
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