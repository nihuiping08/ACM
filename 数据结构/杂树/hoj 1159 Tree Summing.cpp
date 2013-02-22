#include <iostream>
#include <cstdio>
using namespace std;
#define X 100005
int r[X],l[X],nsum,ind;
bool flag;
int dfs(int sum)
{
	int n;
	char ch;
	while(scanf("%c",&ch)&&ch==' '||ch=='\n'||ch=='(');
	if(ch==')')
		return -1;
	cin.putback(ch);
	scanf("%d",&n);
	l[++ind] = dfs(sum+n);
	r[ind] = dfs(sum+n);
	if((r[ind]==-1)&&(l[ind]==-1)&&(sum+n==nsum))
		flag = true;
	while(scanf("%c",&ch)&&ch!=')');
	return ind;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>nsum)
	{
		ind = 0;
		flag = false;
		dfs(0);
		if(flag)
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
	return 0;
}

