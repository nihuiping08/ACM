//ACM ICPC Central European Regional 1997
/*
简单的栈的应用
*/
#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;
const int X = 100005;
int a[X],b[X];
int main()
{
	freopen("sum.in","r",stdin);
	int n,x;
	while(cin>>n)
	{
	    cin>>x;
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
                cout<<"Cheater"<<endl;
                break;
            }
        if(flag)
            cout<<"Not a proof"<<endl;
	}
	return 0;
}
