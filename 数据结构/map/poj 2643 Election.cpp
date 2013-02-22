/*
题目：
	给出竞选人和他的政党，现在给出投的票，问最后谁当权了
分析：
	终于懂得一些map函数的应用，map<string,string> s,就是
	s[string1] = string2;
	同理还有map<string,int> s; s[string] = num； 
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
	map<string,string> s1;//记录竞选人和他的政党
	map<string,int> s2;	//记录当前个人的投票数
	string in1,in2;	//两个输入
	int m,n;
	while(cin>>n)
	{
		getchar();	//一定得有这个getchar()把输进的回车读掉
		for(int i=1;i<=n;i++)
		{
			getline(cin,in1);
			getline(cin,in2);
			s1[in1] = in2;
			s2[in1] = 0;
		}
		cin>>m;
		getchar();	//一定得有这个getchar()把输进的回车读掉
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