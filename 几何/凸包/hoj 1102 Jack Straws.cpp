/*

题目：
    判断线段是否相交，并且相交具有连通性，然后询问任意两点是否相连

分析:
    判断线段相交，发现之前的模板有误，以后改为点积判断是否相交

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 15;
#define debug puts("here");

bool use[X][X];
int n;

struct node
{
    int x,y;
}p[X][2];

int det(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool bet(node a,node b,node o)
{
    int temp = (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
    if(temp<=0)
        return true;
    return false;
}

bool segment(node a,node b,node c,node d)
{
    int d1 = det(a,b,c);
    int d2 = det(a,b,d);
    int d3 = det(c,d,a);
    int d4 = det(c,d,b);
    if(d1*d2<0&&d3*d4<0)
        return true;
    else if(d1==0&&bet(a,b,c))
        return true;
    else if(d2==0&&bet(a,b,d))
        return true;
    else if(d3==0&&bet(c,d,a))
        return true;
    else if(d4==0&&bet(c,d,b))
        return true;
    else
        return false;
}

void floyd()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                use[i][j] = use[i][j]||(use[i][k]&&use[k][j]);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
       for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&p[i][0].x,&p[i][0].y,&p[i][1].x,&p[i][1].y);
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				use[i][j] = use[j][i] = segment(p[i][0],p[i][1],p[j][0],p[j][1]);

		floyd();
		int x,y;
		while(scanf("%d%d",&x,&y),x||y)
			if(use[x][y])
				printf("CONNECTED\n");
			else
				printf("NOT CONNECTED\n");
    }
    return 0;
}
