/*
���������ļ�Ӧ�ã�
�и�ľ�塣�и���Ҫ�������ӣ����и�������ľ��ĳ����й�ϵ���������Ҫ�õ�3��ľ�壬
���ȷֱ�Ϊ8 5 8������ԭʼľ��Ϊ8��5��8��21
 ��Ϊ��ʹ�и����С���ȷֳ�13 �� 8������ӣ���������Ϊ13��8��21��Ȼ��13�ٷָ�Ϊ5 
 �� 8����������Ϊ13����ˣ�This would cost 21+13=34��BUT������ȷָ��16 �� 5 ����21��
 16�ָ�Ϊ8 �� 8������16���ܻ���Ϊ21��16��37������34��������Ż��ѡ�
 ��������Ҫ�õ���������������ֻ��Ҫ��������ܺͣ������ĸ��������빹������
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,t,a,b;
	while(cin>>n)
	{
		long long ans = 0;		//ҪΪlong long�ͲŲ���WA
		priority_queue<int ,vector<int>,greater<int> > q;
		for(int i=0;i<n;i++)
		{
			cin>>t;
			q.push(t);
		}
		if(q.size()==1)
			ans = q.top();
		while(q.size()>1)
		{
			a = q.top();
			q.pop();
			b = q.top();
			q.pop();
			ans += a+b;
			q.push(a+b);
		}
		cout<<ans<<endl;
	}
	return 0;
}