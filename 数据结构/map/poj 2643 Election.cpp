/*
��Ŀ��
	������ѡ�˺��������������ڸ���Ͷ��Ʊ�������˭��Ȩ��
������
	���ڶ���һЩmap������Ӧ�ã�map<string,string> s,����
	s[string1] = string2;
	ͬ����map<string,int> s; s[string] = num�� 
*/
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	map<string,string> s1;//��¼��ѡ�˺���������
	map<string,int> s2;	//��¼��ǰ���˵�ͶƱ��
	string in1,in2;	//��������
	int m,n;
	while(cin>>n)
	{
		getchar();	//һ���������getchar()������Ļس�����
		for(int i=1;i<=n;i++)
		{
			getline(cin,in1);
			getline(cin,in2);
			s1[in1] = in2;
			s2[in1] = 0;
		}
		cin>>m;
		getchar();	//һ���������getchar()������Ļس�����
		for(int i=1;i<=m;i++)
		{
			getline(cin,in1);
			s2[in1]++;
		}
		map<string,int>::iterator it = s2.begin();
		string winner = it->first;
		for(it=s2.begin();it!=s2.end();it++)
			if(it->second>s2[winner])
				winner = it->first;
		bool f = true;
		for(it=s2.begin();it!=s2.end();it++)
			if(s2[winner]==it->second&&it->first!=winner)
			{
				f = false;
				cout<<"tie"<<endl;
				break;
			}
		if(f)
			cout<<s1[winner]<<endl;
	}
	return 0;
}