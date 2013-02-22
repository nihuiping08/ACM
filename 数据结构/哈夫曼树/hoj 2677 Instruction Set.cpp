/*
���������룬����ȨֵΪ a:1 b:1 c:2 d:3 e:5 f:6 ����
	1.��ʼʱ����С�������� a:1 b:1���һ����
	2.�������µ���С�������� 2 c:2 d:3 e:5 f:6 �е� 2 c:2����µ���
	3.��������С�������� 4 d:3 ����µ���
	4.��������С�������� e:5 f:6 ���һ����
	5.��������С�������� 7 11 ���һ�����������γɣ�
	6.����С�ı����ܳ���= 18 + 7 + 11 + 4 + 2 = 42

	2			4			7			11				18
   / \		   / \		   / \		   /  \			   /  \
  a   b		  2   c		  4   d		  e    f		  7   11
			 / \         / \						 / \  / \
			a   b       2	c						4  d  e  f
					   / \						   / \
					  a   b						  2   c
												 / \
												a   b

���������ȶ����������ȶ���ÿ�β��붼�ǲ��뵽�������Ķ���������(���ܲ��Ǻ�׼ȷ)��
����û��ʼ����ʱ���ѳ��ֵĴ������ӣ�����ʼ����ʱ��ÿ�ε���ͷ��������a��b��Ȼ�����������
��Ӻ��ٴν��ӣ�ͬʱ���ȶ��л�������򣬲���ÿ��ans += a+b,���մ𰸼�Ϊans
*/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;
string s;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,command;
	while(cin>>n)
	{
		priority_queue<int ,vector<int>,greater<int> > q;	//ע�⣬�˴�> >���пո��
		int worst = 0,ans = 0;
		for(int i=0;i<n;i++)
		{
			cin>>s>>command;
			worst+=command*s.size();		//������Ҫ�Ŀռ�
			q.push(command);				//�����ݽ���
		}
		int a,b;
		if(q.size()==1)						//��֮��һ����ʱ
			ans = q.top();
		while(true)
		{
			a = q.top();
			q.pop();
			if(q.empty())	//ֻʣ��һ�����ڵ㣬���Ѿ�������һ����
				break;
			b = q.top();
			q.pop();
			ans+=a+b;		//��
			q.push(a+b);	//�������ɵ�����Ȩֵ����
		}
		cout<<worst<<" "<<ans<<endl;
	}
	return 0;
}