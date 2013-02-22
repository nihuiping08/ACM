//ACM ICPC Central European Regional 1997
/*
简单的栈的应用，可惜WA了好几次
*/
#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;
const int X = 1005;
int a[X],b[X];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,x,t = 0;
	while(cin>>n,n)
	{
		if(t++)
			cout<<endl;
		while(cin>>x,x)
		{
			stack<int> s;
			a[1] = x;
			for(int i=2;i<=n;i++)
				scanf("%d",a+i);
			int cnt = 1;
			int B = 1;
			for(int i=1;i<=n;i++)
			{
				s.push(i);
				if(s.top()==a[cnt])
				{
					while(!s.empty())
					{
						if(s.top()==a[cnt])
						{
							b[B++] = s.top();
							cnt++;
							s.pop();
						}
						else
							break;
					}
				}
			}
			bool flag = true;
			for(int i=1;i<=n;i++)
				if(a[i]!=b[i])
				{
					flag = false;
					cout<<"No"<<endl;
					break;
				}
			if(flag)
				cout<<"Yes"<<endl;
		}
	}
	cout<<endl;
	return 0;
}