/*

题目：
	已知经度纬度，问两地的距离。没有自己动手做，只是套了一下模板。。。

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <map>
using namespace std;
#define X 105
#define PI 3.141592653589793
long double cal(long double x1,long double y1,long double x2,long double y2,long double r)
{		//纬度1，经度1，纬度2，经度2，球半径
	//return r*(acos(cos(x1)*cos(x2)*cos(y1-y2)+sin(x1)*sin(x2)));
	double x = x2-x1;	//纬度
	double y = y2-y1;	//经度
	double a = pow((sin(x/2)),2)+cos(x1)*cos(x2)*pow((sin(y/2)),2);
	double c = 2*atan2(sqrt(a),sqrt(1-a));
	return r*c;
}
string city[X];
int cnt;
long double x[X],y[X];
int find(string s)
{
	for(int i=1;i<=cnt;i++)
		if(s==city[i])
			return i;
	return -1;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	long double r = 6378;
	int id1,id2;
	while(cin>>city[1]>>x[1]>>y[1])
	{
		cnt = 1;
		string s,q;
		//x[1] = x[1];
		while(cin>>s,s!="#")
		{
			city[++cnt] = s;
			cin>>x[cnt]>>y[cnt];
			//x[cnt] = x[cnt];
		}
		bool flag = false;
		while(cin>>s>>q,s!="#"||q!="#")
		{
			if(flag)
				cout<<endl;
			else
				flag = true;
			cout<<s<<" - "<<q<<endl;
			id1 = find(s);
			id2 = find(q);
			if(id1==-1||id2==-1)
				printf("Unknown\n");
			else
				printf("%d km\n",(int)(cal(x[id1]*PI/180,y[id1]*PI/180,x[id2]*PI/180,y[id2]*PI/180,r)+0.5));
		}
	}

	return 0;
}