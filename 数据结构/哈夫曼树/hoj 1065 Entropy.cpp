/*
	HUFFMAN��,�����ݽṹ�кܻ����Ķ�����,��ǰд����HUFFMAN����ĳ���,
	���Ǹо�����û�б�Ҫ��HUFFMANȫ�������,һ�ֲ���Ľⷨ,��ʹ�����ȶ��������.
	�������ȶ���priority_queue��STL���е�,������ͷ�ļ�<queue>��,���Զ����·�����е����ݽ�������,
	������õ��Ƕ�ͷ����С������ʽ.ÿ��ȡ��ǰ����(Ҳ����Ȩֵ��С�����ڵ�)�����µĽڵ�,�ٷ����
	����,ֱ��ȡ�����һ��Ϊֹ,��Ҳ����HUFFMAN���Ĺ������..

*/
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
string s;
int d[27];
//int cmp(const void *a,const void *b);
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(getline(cin,s),s!="END")
	{
		memset(d,0,sizeof(d));
		int len = s.size();
		int worst = len<<3;		//������λ�������
		priority_queue<int ,vector<int>,greater<int> > q;
		//ע���������> >��������>>��>>��һ�����ţ�PE4��
		//���ַ��������򲢽��ַ��������η������ȶ����� 
		sort(s.begin(),s.end());	//���ַ����е���ĸ����
		char ch = s[0];
		int times = 0;
		for(int i=0;i<len;i++)		//ͳ��ÿ����ĸ�ֱ�ĳ��ִ���
		{
			if(s[i]==ch)
				times++;
			else
			{
				q.push(times);
				ch = s[i];
				times = 1;
			}
		}
		q.push(times);

		//����Huffman���Ĺ���  
		int ans = 0,a,b;
		if(q.size()==1)
			ans = q.top();
		while(true)
		{
			a = q.top();	//�ҵ����ȶ�������С��һ����
			q.pop();
			if(q.empty())	//�����ʱΪ�գ������˳���ǰѭ��
				break;
			b = q.top();	//�ҵ����ȶ����е���Сһ����(ע��֮ǰ����С�����Ѿ�����)
			q.pop();
			ans += a+b;
			q.push(a+b);		//���������ϲ�Ϊͬһ����
		}
		printf("%d %d %.1lf\n",worst,ans,worst*1.0/ans);
	}
	return 0;
}

